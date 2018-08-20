// ==========  GameController.framework/Headers/GCExtendedGamepadSnapshot.h
//
//  GCExtendedGamepadSnapshot.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <GameController/GameController.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A GCExtendedGamepadSnapshot snapshot is a concrete GCExtendedGamepad implementation. It can be used directly in an
 application to implement controller input replays. It is also returned as the result of polling a controller.
 
 The current snapshotData is readily available to access as NSData. A developer can serialize this to any
 destination necessary using the NSData API.
 
 The data contains some version of a GCExtendedGamepadSnapShotData structure.

 @see -[GCExtendedGamepad saveSnapshot]
 */
GAMECONTROLLER_EXPORT
@interface GCExtendedGamepadSnapshot : GCExtendedGamepad
@property (atomic, copy) NSData *snapshotData;

- (instancetype)initWithSnapshotData:(NSData *)data;
- (instancetype)initWithController:(GCController *)controller snapshotData:(NSData *)data;

@end

#pragma pack(push, 1)
typedef struct {
    // Standard information
    uint16_t version; //0x0100
    uint16_t size;    //sizeof(GCExtendedGamepadSnapShotDataV100) or larger
    
    // Extended gamepad data
    // Axes in the range [-1.0, 1.0]
    float dpadX;
    float dpadY;
    
    // Buttons in the range [0.0, 1.0]
    float buttonA;
    float buttonB;
    float buttonX;
    float buttonY;
    float leftShoulder;
    float rightShoulder;

    // Axes in the range [-1.0, 1.0]
    float leftThumbstickX;
    float leftThumbstickY;
    float rightThumbstickX;
    float rightThumbstickY;
    
    // Buttons in the range [0.0, 1.0]
    float leftTrigger;
    float rightTrigger;

} GCExtendedGamepadSnapShotDataV100;
#pragma pack(pop)

/**Fills out a v100 snapshot from any compatible NSData source
 
 @return NO if data is nil, snapshotData is nil or the contents of data does not contain a compatible snapshot. YES for all other cases.
 */
GAMECONTROLLER_EXPORT
BOOL GCExtendedGamepadSnapShotDataV100FromNSData(GCExtendedGamepadSnapShotDataV100 *__nullable snapshotData, NSData *__nullable data);

/**Creates an NSData object from a v100 snapshot.
 If the version and size is not set in the snapshot the data will automatically have version 0x100 and sizeof(GCExtendedGamepadSnapShotDataV100) set as the values implicitly.
 
 @return nil if the snapshot is NULL, otherwise an NSData instance compatible with GCExtendedGamepadSnapshot.snapshotData
 */
GAMECONTROLLER_EXPORT
NSData *__nullable NSDataFromGCExtendedGamepadSnapShotDataV100(GCExtendedGamepadSnapShotDataV100 *__nullable snapshotData);

NS_ASSUME_NONNULL_END
// ==========  GameController.framework/Headers/GCControllerButtonInput.h
//
//  GCControllerButtonInput.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <GameController/GameController.h>

NS_ASSUME_NONNULL_BEGIN

GAMECONTROLLER_EXPORT
@interface GCControllerButtonInput : GCControllerElement

/**
 Set this block if you want to be notified when the value on this button changes.
 
 @param button the element that has been modified.
 @param value the value the button was set to at the time the valueChangedHandler fired.
 @param pressed the pressed state of the button at the time the valueChangedHandler fired.
 @see value
 @see pressed
 */
typedef void (^GCControllerButtonValueChangedHandler)(GCControllerButtonInput *button, float value, BOOL pressed);
@property (nonatomic, copy, nullable) GCControllerButtonValueChangedHandler valueChangedHandler;

/**
 Set this block if you want to be notified when only the pressed state on this button changes. This
 will get called less often than the valueChangedHandler with the additional feature of the pressed state
 being different to the last time it was called.
 */
@property (nonatomic, copy, nullable) GCControllerButtonValueChangedHandler pressedChangedHandler NS_AVAILABLE(10_10, 8_0);

/**
 A normalized value for the input. Between 0 and 1 for button inputs. Values are saturated and thus never exceed the range of [0, 1].
 @see valueChangedHandler
 @see pressed
 */
@property (nonatomic, readonly) float value;

/**
 Buttons are mostly used in a digital sense, thus we have a recommended method for checking for pressed state instead of
 interpreting the value.
 
 As a general guideline a button is pressed if the value exceeds 0. However there may be hysterisis applied
 to counter noisy input values, thus incidental values around the threshold value may not trigger a change
 in pressed state.
 @see pressedChangedHandler
 @see value
 */
@property (nonatomic, readonly, getter = isPressed) BOOL pressed;

@end

NS_ASSUME_NONNULL_END

// ==========  GameController.framework/Headers/GCGamepad.h
//
//  GCGamepad.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <GameController/GameController.h>

NS_ASSUME_NONNULL_BEGIN

@class GCController;
@class GCGamepadSnapshot;

/**
 Standard Gamepad profile.
 
 All controller profiles provide a base level of information about the controller they belong to.
 
 A profile maps the hardware notion of a controller into a logical controller. One that a developer can design for
 and depend on, no matter the underlying hardware.
 */
GAMECONTROLLER_EXPORT
@interface GCGamepad : NSObject

/**
 A profile keeps a reference to the controller that this profile is mapping input from.
 */
#if !__has_feature(objc_arc)
@property (nonatomic, readonly, assign) GCController *controller;
#else
@property (nonatomic, readonly, weak) GCController *controller;
#endif

/**
 Set this block if you want to be notified when a value on a element changed. If multiple elements have changed this block will be called
 for each element that changed. As elements in a collection, such as the axis in a dpad, tend to change at the same time and thus
 will only call this once with the collection as the element.
 
 @param gamepad this gamepad that is being used to map the raw input data into logical values on controller elements such as the dpad or the buttons.
 @param element the element that has been modified.
 */
typedef void (^GCGamepadValueChangedHandler)(GCGamepad *gamepad, GCControllerElement *element);
@property (nonatomic, copy, nullable) GCGamepadValueChangedHandler valueChangedHandler;

/**
 Polls the state vector of the controller and saves it to a snapshot. The snapshot is stored in a device independent
 format that can be serialized and used at a later date. This is useful for features such as quality assurance,
 save game or replay functionality among many.
 
 If your application is heavily multithreaded this may also be useful to guarantee atomicity of input handling as
 a snapshot will not change based on user input once it is taken.
 */
- (GCGamepadSnapshot *)saveSnapshot;

/**
 Required to be analog in the Standard profile. All the elements of this directional input are thus analog.
 */
@property (nonatomic, readonly) GCControllerDirectionPad *dpad;

/**
 All face buttons are required to be analog in the Standard profile. These must be arranged
 in the diamond pattern given below:
 
   Y
  / \
 X   B
  \ /
   A
 
 */
@property (nonatomic, readonly) GCControllerButtonInput *buttonA;
@property (nonatomic, readonly) GCControllerButtonInput *buttonB;
@property (nonatomic, readonly) GCControllerButtonInput *buttonX;
@property (nonatomic, readonly) GCControllerButtonInput *buttonY;

/**
 Shoulder buttons are required to be analog inputs.
 */
@property (nonatomic, readonly) GCControllerButtonInput *leftShoulder;
/**
 Shoulder buttons are required to be analog inputs.
 */
@property (nonatomic, readonly) GCControllerButtonInput *rightShoulder;

@end

NS_ASSUME_NONNULL_END
// ==========  GameController.framework/Headers/GCExtendedGamepad.h
//
//  GCExtendedGamepad.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <GameController/GameController.h>

NS_ASSUME_NONNULL_BEGIN

@class GCController;
@class GCExtendedGamepadSnapshot;

/**
 Extended Gamepad profile. Has all the physical features of a Standard Gamepad and more.
 
 In comparison to the Standard gamepad, The directional pad on an Extended gamepad is optionally analog
 as the two thumbsticks provided are required to be analog.
 
 All controller profiles provide a base level of information about the controller they belong to.
 
 A profile maps the hardware notion of a controller into a logical controller. One that a developer can
 design for and depend on, no matter the underlying hardware.
 */
GAMECONTROLLER_EXPORT
@interface GCExtendedGamepad : NSObject

/**
 A profile keeps a reference to the controller that this profile is mapping input from.
 */
#if !__has_feature(objc_arc)
@property (nonatomic, readonly, assign) GCController *controller;
#else
@property (nonatomic, readonly, weak) GCController *controller;
#endif

/**
 Set this block if you want to be notified when a value on a element changed. If multiple elements have changed this block will be called
 for each element that changed. As elements in a collection, such as the axis in a dpad, tend to change at the same time and thus
 will only call this once with the collection as the element.
 
 @param gamepad this gamepad that is being used to map the raw input data into logical values on controller elements such as the dpad or the buttons.
 @param element the element that has been modified.
 */
typedef void (^GCExtendedGamepadValueChangedHandler)(GCExtendedGamepad *gamepad, GCControllerElement *element);
@property (nonatomic, copy, nullable) GCExtendedGamepadValueChangedHandler valueChangedHandler;

/**
 Polls the state vector of the controller and saves it to a snapshot. The snapshot is stored in a device independent
 format that can be serialized and used at a later date. This is useful for features such as quality assurance,
 save game or replay functionality among many.
 
 If your application is heavily multithreaded this may also be useful to guarantee atomicity of input handling as
 a snapshot will not change based on user input once it is taken.
 */
- (GCExtendedGamepadSnapshot *)saveSnapshot;

/**
 Required to be analog in the Extended profile. All the elements of this directional input are thus analog.
 */
@property (nonatomic, readonly) GCControllerDirectionPad *dpad;

/**
 All face buttons are required to be analog in the Extended profile. These must be arranged
 in the diamond pattern given below:
 
   Y
  / \
 X   B
  \ /
   A
 
 */
@property (nonatomic, readonly) GCControllerButtonInput *buttonA;
@property (nonatomic, readonly) GCControllerButtonInput *buttonB;
@property (nonatomic, readonly) GCControllerButtonInput *buttonX;
@property (nonatomic, readonly) GCControllerButtonInput *buttonY;

/**
 A thumbstick is a 2-axis control that is physically required to be analog. All the elements of this directional input are thus analog.
 */
@property (nonatomic, readonly) GCControllerDirectionPad *leftThumbstick;

/**
 A thumbstick is a 2-axis control that is physically required to be analog. All the elements of this directional input are thus analog.
 */
@property (nonatomic, readonly) GCControllerDirectionPad *rightThumbstick;

/**
 Shoulder buttons are required to be analog inputs.
 */
@property (nonatomic, readonly) GCControllerButtonInput *leftShoulder;
/**
 Shoulder buttons are required to be analog inputs.
 */
@property (nonatomic, readonly) GCControllerButtonInput *rightShoulder;

/**
 Triggers are required to be analog inputs. Common uses would be acceleration and decelleration in a driving game for example.
 */
@property (nonatomic, readonly) GCControllerButtonInput *leftTrigger;
@property (nonatomic, readonly) GCControllerButtonInput *rightTrigger;

@end

NS_ASSUME_NONNULL_END
// ==========  GameController.framework/Headers/GCGamepadSnapshot.h
//
//  GCGamepadSnapshot.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <GameController/GameController.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A GCGamepadSnapshot snapshot is a concrete GCGamepad implementation. It can be used directly in an
 application to implement controller input replays. It is also returned as the result of polling
 a controller.
 
 The current snapshotData is readily available to access as NSData. A developer can serialize this to any
 destination necessary using the NSData API.
 
 The data contains some version of a GCGamepadSnapShotData structure.
 
 @see -[GCGamepad saveSnapshot]
 */
GAMECONTROLLER_EXPORT
@interface GCGamepadSnapshot : GCGamepad
@property (atomic, copy) NSData *snapshotData;

- (instancetype)initWithSnapshotData:(NSData *)data;
- (instancetype)initWithController:(GCController *)controller snapshotData:(NSData *)data;

@end

#pragma pack(push, 1)
typedef struct {
    // Standard information
    uint16_t version; //0x0100
    uint16_t size;    //sizeof(GCGamepadSnapShotDataV100) or larger
    
    // Standard gamepad data
    // Axes in the range [-1.0, 1.0]
    float dpadX;
    float dpadY;
    
    // Buttons in the range [0.0, 1.0]
    float buttonA;
    float buttonB;
    float buttonX;
    float buttonY;
    float leftShoulder;
    float rightShoulder;
    
} GCGamepadSnapShotDataV100;
#pragma pack(pop)

/**Fills out a v100 snapshot from any compatible NSData source
 
 @return NO if data is nil, snapshotData is nil or the contents of data does not contain a compatible snapshot. YES for all other cases.
 */
GAMECONTROLLER_EXPORT
BOOL GCGamepadSnapShotDataV100FromNSData(GCGamepadSnapShotDataV100 *__nullable snapshotData, NSData *__nullable data);

/**Creates an NSData object from a v100 snapshot.
 If the version and size is not set in the snapshot the data will automatically have version 0x100 and sizeof(GCGamepadSnapShotDataV100) set as the values implicitly.
 
 @return nil if the snapshot is NULL, otherwise an NSData instance compatible with GCGamepadSnapshot.snapshotData
 */
GAMECONTROLLER_EXPORT
NSData *__nullable NSDataFromGCGamepadSnapShotDataV100(GCGamepadSnapShotDataV100 *__nullable snapshotData);

NS_ASSUME_NONNULL_END
// ==========  GameController.framework/Headers/GCControllerAxisInput.h
//
//  GCControllerAxisInput.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <GameController/GameController.h>

NS_ASSUME_NONNULL_BEGIN

GAMECONTROLLER_EXPORT
@interface GCControllerAxisInput : GCControllerElement

/**
 Set this block if you want to be notified when the value on this axis changes.
 
 @param axis the element that has been modified.
 @param value the value the axis was set to at the time the valueChangedHandler fired.
 */
typedef void (^GCControllerAxisValueChangedHandler)(GCControllerAxisInput *axis, float value);
@property (nonatomic, copy, nullable) GCControllerAxisValueChangedHandler valueChangedHandler;

/**
 A normalized value for the input, between -1 and 1 for axis inputs. The values are deadzoned and saturated before they are returned
 so there is no value ouside the range. Deadzoning does not remove values from the range, the full 0 to 1 magnitude of values
 are possible from the input.

 As an axis is often used in a digital sense, you can rely on a value of 0 meaning the axis is inside the deadzone.
 Any value greater than or less than zero is not in the deadzone.
 */
@property (nonatomic, readonly) float value;

@end

NS_ASSUME_NONNULL_END

// ==========  GameController.framework/Headers/GCControllerDirectionPad.h
//
//  GCControllerDirectionPad.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <GameController/GameController.h>

@class GCControllerAxisInput;

NS_ASSUME_NONNULL_BEGIN

/**
 A direction pad is a common grouping of 2 axis inputs where the input can also be interpreted as 2 sets of mutually exclusive button pairs.
 Only one button in each pair, {up, down} and {left, right}, can be pressed at any one time.
 */
GAMECONTROLLER_EXPORT
@interface GCControllerDirectionPad : GCControllerElement

/**
 Set this block if you want to be notified when the value on this axis changes.
 
 @param dpad the direction pad collection whose axis have been modified.
 @param xValue the value the x axis was set to at the time the valueChangedHandler fired.
 @param yValue the value the y axis was set to at the time the valueChangedHandler fired.
 */
typedef void (^GCControllerDirectionPadValueChangedHandler)(GCControllerDirectionPad *dpad, float xValue, float yValue);
@property (nonatomic, copy, nullable) GCControllerDirectionPadValueChangedHandler valueChangedHandler;

@property (nonatomic, readonly) GCControllerAxisInput *xAxis;
@property (nonatomic, readonly) GCControllerAxisInput *yAxis;

@property (nonatomic, readonly) GCControllerButtonInput *up;
@property (nonatomic, readonly) GCControllerButtonInput *down;

@property (nonatomic, readonly) GCControllerButtonInput *left;
@property (nonatomic, readonly) GCControllerButtonInput *right;

@end

NS_ASSUME_NONNULL_END
// ==========  GameController.framework/Headers/GameController.h
//
//  GameController.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#if TARGET_OS_IPHONE
#import <UIKit/UIViewController.h>
#else
#import <AppKit/NSViewController.h>
#endif

#ifdef __cplusplus
#define GAMECONTROLLER_EXTERN		extern "C" __attribute__((visibility ("default")))
#else
#define GAMECONTROLLER_EXTERN	        extern __attribute__((visibility ("default")))
#endif

#define GAMECONTROLLER_EXPORT NS_CLASS_AVAILABLE(10_9, 7_0)

#import <GameController/GCControllerElement.h>

#import <GameController/GCControllerAxisInput.h>
#import <GameController/GCControllerButtonInput.h>
#import <GameController/GCControllerDirectionPad.h>

#import <GameController/GCMotion.h>

#import <GameController/GCGamepad.h>
#import <GameController/GCGamepadSnapshot.h>

#import <GameController/GCExtendedGamepad.h>
#import <GameController/GCExtendedGamepadSnapshot.h>

#import <GameController/GCController.h>
// ==========  GameController.framework/Headers/GCController.h
//
//  GCController.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <GameController/GameController.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Use these constants with NSNotificationCenter to listen to connection and disconnection events.
 
 Use GCControllerDidConnectNotification for observing connections of controllers.
 Use GCControllerDidDisconnectNotification for observing disconnections of controllers.
 
 Connections and disconnections of controllers will also be reflected in the controllers array
 of the GCController class.
 
 The 'object' property of the notification will contain the GCController that was connected or disconnected.
 For example:
 
 - (void)controllerDidConnect:(NSNotification *)note {
 
 GCController *controller = note.object;
 
 ....
 }
 
 @see NSNotificationCenter
 @see GCController.controllers
 */
GAMECONTROLLER_EXTERN NSString *const GCControllerDidConnectNotification;
GAMECONTROLLER_EXTERN NSString *const GCControllerDidDisconnectNotification;

/**
 This is the player index that a connected controller will have if it has never been assigned a player index on the current system.
 Controllers retain the player index they have been assigned between game sessions, so if you wish to unset the player index of a
 controller set it back to this value.
 */
typedef NS_ENUM(NSInteger, GCControllerPlayerIndex) {
    GCControllerPlayerIndexUnset = -1,
    GCControllerPlayerIndex1 = 0,
    GCControllerPlayerIndex2,
    GCControllerPlayerIndex3,
    GCControllerPlayerIndex4,
};

/**
 Controllers are available to an application that links to GameController.framework. There are 2 ways to access controllers
 paired to the system, adopt both to ensure the best user experience:
 
 1: Querying for the the current array or controllers using [GCController controllers].
 2: Registering for Connection/Disconnection notifications from NSNotificationCenter.
 
 Only controllers that support one of the allowed profiles, such as GCGamepad, will be enumerated. Check for the profile
 supported before using a controller in your application. Ignore a controller that doesn't support a profile that suits
 your application, as the user will expect their controller to either be fully supported or not supported at all.
  */
GAMECONTROLLER_EXPORT
@interface GCController : NSObject

/**
 Set this block to be notified when a user intends to suspend or resume the current game state. A controller will have a button
 dedicated to suspending and resuming play and invoking context sensitive actions. During event handling the system will
 notify the application using this block such that the application can handle the suspension and resumption from the given controller.
 
 Use this to implement your canonical transition to a pause menu for example if that is your application's desired handling
 of suspension in play. You may pause and resume base don game state as well so the event is only called each time the
 pause/resume button is pressed.
 */
@property (nonatomic, copy, nullable) void (^controllerPausedHandler)(GCController *controller);

/**
 The dispatch queue that element value change handlers are submitted on. The default queue is main, and setting this to any
 other queue will make value change handlers dispatch async on the given queue. This is useful if the main game loop
 of the application is not on main, or if input logic is handled on another thread from the main game loop.
 
 @see GCControllerAxisInput.valueChangedHandler
 @see GCControllerButtonInput.valueChangedHandler
 @see GCControllerButtonInput.pressedChangedHandler
 @see GCControllerDirectionPad.valueChangedHandler
 @see GCMotion.valueChangedHandler
 */
#if defined(OS_OBJECT_USE_OBJC) && OS_OBJECT_USE_OBJC==1
@property (retain) dispatch_queue_t handlerQueue;
#else
@property (assign) dispatch_queue_t handlerQueue;
#endif

/**
 A vendor supplied name. May be nil, and is not guaranteed to be unique. This should not be used as a key in a dictionary,
 but simply as a way to present some basic information about the controller in testing or to the user.
 */
@property (nonatomic, readonly, copy, nullable) NSString *vendorName;

/**
 A controller may be form fitting or otherwise closely attached to the device. This closeness to other inputs on the device
 may suggest that interaction with the device may use other inputs easily. This is presented to developers to allow them to
 make informed descisions about UI and interactions to choose for their game in this situation.
 */
@property (nonatomic, readonly, getter = isAttachedToDevice) BOOL attachedToDevice;

/**
 A player index for the controller, defaults to GCControllerPlayerIndexUnset, unless the controller previously had
 a player index assigned to it on the current user's system.
 
 This can be set both for the application to keep track of controllers and as a signal to make a controller display a player
 index on a set of LEDs or some other mechanism.
 
 A controller is not guranteed to have a visual display of the playerIndex, but the API will keep track of the playerIndex
 for a controller while connected and in between being disconnected and connected again. Thus playerIndex persists for a controller
 with regards to a system. This makes it useful for persisting player-controller assignments across game sessions.
 
 Negative values less than GCControllerPlayerIndexUnset will just map back to GCControllerPlayerIndexUnset when read back.
 */
@property (nonatomic) GCControllerPlayerIndex playerIndex;

/**
 Gets the profile for the controller that suits current application.
 
 There are two supported profiles, with an additional optional profile for motion as well. 
 Each controller may be able to map its inputs into all profiles or just one kind of profile. Query for the controller
 profile that suits your game, the simplest kind will be supported by the broadest variety
 of controllers. A controller supporting the Extended Gamepad profile for example supports the Gamepad profile and more.
 As such it can always be used just in the Gamepad profile if that suits the game.
 
 A physical controller that supports a profile must support it completely. That means that all buttons and axis inputs must
 be valid inputs that a developer can utilize.
 
 If a controller does not support the given profile the returned value will be nil. Use this to filter controllers if the
 application requires a specific kind of profile.
 @see motion
 */
@property (nonatomic, retain, readonly, nullable) GCGamepad *gamepad;
@property (nonatomic, retain, readonly, nullable) GCExtendedGamepad *extendedGamepad;

/**
 Gets the motion input profile. This profile is optional and may be available if the controller is attached to a device that supports motion.
 If this is nil the controller does not support motion input and only the gamepad & extendedGamepad profiles are available.
 @see gamepad
 @see extendedGamepad
 */
@property (nonatomic, retain, readonly, nullable) GCMotion *motion NS_AVAILABLE(10_10, 8_0);

/**
 Get a list of controllers currently attached to the system.
 
 @see GCControllerDidConnectNotification
 @see GCControllerDidDisconnectNotification
 */
+ (NSArray<GCController *> *)controllers;

/**
 Start discovery of new wireless controllers that are discoverable. This is an asynchronous and the supplied completionHandler
 will get called once no more devices can be found. If there are already multiple controllers available for use, there
 may be little reason to automatically start discovery of new wireless controllers. In this situation it may be best to
 allow the user to start discovery manually via in-game UI.
 
 Once discovery has started new controllers will notify themselves as connected via GCControllerDidConnectNotification.
 As the notification arrives the controller is also available in the controllers array.

 The completionHandler could be used to update UI and/or game state to indicate that no more controllers will be found
 and the current set of controllers is what is available for use in the game.
 
 If a completionHandler was provided, it will be called once when discovery stops. Either from an explicit call to
 stopWirelessControllerDiscovery or from timing out or stopping in its natural course of operation. Thus the
 completionHandler will at most be called once per call to startWirelessControllerDiscoveryWithCompletionHandler:.
 
 The completionHandler may also not get called at all, if for example startWirelessControllerDiscoveryWithCompletionHandler:
 is called multiple times during dicovery. For this case the net effect is that the completionHandler is replaced with each call
 and only the last one set before discovery stops will be called.
 
 @param completionHandler an optional handler that is called when discovery stops. (may be nil, in which case you will not be notified when discovery stops)
 @see stopWirelessControllerDiscovery
 @see controllers
 */
+ (void)startWirelessControllerDiscoveryWithCompletionHandler:(nullable void (^)(void))completionHandler;

/**
 If no more controllers are needed, depending on game state or number of controllers supported by a game, the discovery
 process can be stopped. Calling stopWirelessControllerDiscovery when no discovery is currently in progress will return
 immediately without any effect, thus it is safe to call even if the completionHandler of
 startWirelessControllerDiscoveryWithCompletionHandler: has been called.
 
 @see startWirelessControllerDiscoveryWithCompletionHandler:
 */
+ (void)stopWirelessControllerDiscovery;

@end

NS_ASSUME_NONNULL_END

// ==========  GameController.framework/Headers/GCControllerElement.h
//
//  GCControllerElement.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Every controller element knows which collection it belongs to and whether its input value is analog or digital.
 */
NS_CLASS_AVAILABLE(10_9, 7_0)
@interface GCControllerElement : NSObject

/**
 Each element can be part of a wider collection of inputs that map to a single logical element. A directional pad (dpad)
 is a logical collection of two axis inputs and thus each axis belongs to the same collection element - the dpad.
 */
#if !__has_feature(objc_arc)
@property (nonatomic, assign, readonly) GCControllerElement *collection;
#else
@property (nonatomic, weak, readonly, nullable) GCControllerElement *collection;
#endif

/**
 Check if the element can support more than just digital values, such as decimal ranges between 0 and 1.
 Defaults to YES for most elements.
 */
@property (nonatomic, readonly, getter = isAnalog) BOOL analog;

@end

NS_ASSUME_NONNULL_END
// ==========  GameController.framework/Headers/GCMotion.h
//
//  GCMotion.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <GameController/GameController.h>

NS_ASSUME_NONNULL_BEGIN

@class GCController;

/**
 A 3 dimensional acceleration vector measured as scalar multiples of earth's gravitational acceleration, G.
 
 The azimuth direction is assumed to be (0, 0, 1), so a device held at rest with the z axis aligned with the azimuth
 is assumed to have gravitation applying the vector (0, 0, -1).
 
 @field x X-axis acceleration as a scalar multiple of earth's gravitational acceleration, G.
 @field y Y-axis acceleration as a scalar multiple of earth's gravitational acceleration, G.
 @field z Z-axis acceleration as a scalar multiple of earth's gravitational acceleration, G.
 */
typedef struct {
    double x, y, z;
} GCAcceleration;

/**
 A structure containing 3-axis rotation rate data.
 
 
 @field x   X-axis rotation rate in radians/second. The sign follows the right hand
            rule (i.e. if the right hand is wrapped around the X axis such that the 
            tip of the thumb points toward positive X, a positive rotation is one
            toward the tips of the other 4 fingers).
 
 @field y   Y-axis rotation rate in radians/second. The sign follows the right hand 
            rule (i.e. if the right hand is wrapped around the Y axis such that the 
            tip of the thumb points toward positive Y, a positive rotation is one   
            toward the tips of the other 4 fingers).
 @field z
            Z-axis rotation rate in radians/second. The sign follows the right hand
            rule (i.e. if the right hand is wrapped around the Z axis such that the
            tip of the thumb points toward positive Z, a positive rotation is one
            toward the tips of the other 4 fingers).
 */
typedef struct {
	double x, y, z;
} GCRotationRate;


/**
 A structure containing 3-axis rotation data. The angles are rotated in order or pitch then yaw then roll.
 
 
 @field pitch X-axis rotation in radians. The sign follows the right hand
 rule (i.e. if the right hand is wrapped around the X axis such that the
 tip of the thumb points toward positive X, a positive rotation is one
 toward the tips of the other 4 fingers).
 
 @field yaw   Y-axis rotation in radians. The sign follows the right hand
 rule (i.e. if the right hand is wrapped around the Y axis such that the
 tip of the thumb points toward positive Y, a positive rotation is one
 toward the tips of the other 4 fingers).
 
 @field roll  Z-axis rotation in radians. The sign follows the right hand
 rule (i.e. if the right hand is wrapped around the Z axis such that the
 tip of the thumb points toward positive Z, a positive rotation is one
 toward the tips of the other 4 fingers).
 */
typedef struct {
    double pitch, yaw, roll;
} GCEulerAngles;

/**
 Represents a quaternion (one way of parameterizing attitude).
 If q is an instance of GCQuaternion, mathematically it represents the following quaternion:
 
 		q.x*i + q.y*j + q.z*k + q.w
 
 */
typedef struct GCQuaternion {
    double x, y, z, w;
} GCQuaternion;


/**
 A profile for getting motion input from a controller that has the ability to measure acceleration
 and rotation rate. 
 
 You check for the availablity of motion inputs by getting the motion property
 of a controller. If that returns a nil value; motion is not available. A non-nil value is a valid
 GCMotion profile that is able to provide motion input.
 
 @see GCController.motion
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface GCMotion : NSObject

/**
 A profile keeps a reference to the controller that it is mapping input from.
 
 @see GCController
 */
#if !__has_feature(objc_arc)
@property (nonatomic, readonly, assign) GCController *controller;
#else
@property (nonatomic, readonly, weak) GCController *controller;
#endif

/**
 Called whenever a motion value changed.
 */
typedef void (^GCMotionValueChangedHandler)(GCMotion *motion);
@property (nonatomic, copy, nullable) GCMotionValueChangedHandler valueChangedHandler;

/**
 The gravity vector expressed in the controller's reference frame.
 
 Note that the total acceleration of the controller is equal to gravity plus userAcceleration.
 
 @see userAcceleration
 */
@property (nonatomic, assign, readonly) GCAcceleration gravity;

/**
 The acceleration that the user is giving to the controller.
 
 Note that the total acceleration of the controller is equal to gravity plus userAcceleration.
 
 @see userAcceleration
 */
@property (nonatomic, assign, readonly) GCAcceleration userAcceleration;

/**
 The current attitude of the controller.
 */
@property (nonatomic, assign, readonly) GCQuaternion attitude;

/**
 The current rotation rate of the controller.
 */
@property (nonatomic, assign, readonly) GCRotationRate rotationRate;

@end

NS_ASSUME_NONNULL_END