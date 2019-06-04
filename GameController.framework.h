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
API_DEPRECATED("GCExtendedGamepadSnapshot has been deprecated, use [GCController controllerWithExtendedGamepad] instead", macos(10.11, 10.15), ios(9.0, 13.0), tvos(9.0, 13.0))
@interface GCExtendedGamepadSnapshot : GCExtendedGamepad
@property (atomic, copy) NSData *snapshotData;

- (instancetype)initWithSnapshotData:(NSData *)data;
- (instancetype)initWithController:(GCController *)controller snapshotData:(NSData *)data;

@end

typedef NS_ENUM(NSInteger, GCExtendedGamepadSnapshotDataVersion) {
    GCExtendedGamepadSnapshotDataVersion1 = 0x0100,
    GCExtendedGamepadSnapshotDataVersion2 = 0x0101
} API_DEPRECATED("GCExtendedGamepadSnapshot has been deprecated, use [GCController controllerWithExtendedGamepad] instead", macos(10.11, 10.15), ios(9.0, 13.0), tvos(9.0, 13.0));

extern const GCExtendedGamepadSnapshotDataVersion GCCurrentExtendedGamepadSnapshotDataVersion API_DEPRECATED("GCExtendedGamepadSnapshot has been deprecated, use [GCController controllerWithExtendedGamepad] instead", macos(10.11, 10.15), ios(9.0, 13.0), tvos(9.0, 13.0));

#pragma pack(push, 1)
typedef struct {
    
#pragma mark - GCExtendedGamepadSnapshotDataVersion1+
    uint16_t version;
    uint16_t size;
    
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
    
#pragma mark - GCExtendedGamepadSnapshotDataVersion2+
    // Boolean indicating whether the controller supports clickable thumbsticks (1) or not (0)
    BOOL supportsClickableThumbsticks API_AVAILABLE(macos(10.14.1), ios(12.1), tvos(12.1));
    
    // Left and right thumbstick clickable values (0, 1)
    BOOL leftThumbstickButton API_AVAILABLE(macos(10.14.1), ios(12.1), tvos(12.1));
    BOOL rightThumbstickButton API_AVAILABLE(macos(10.14.1), ios(12.1), tvos(12.1));
    
} GCExtendedGamepadSnapshotData API_DEPRECATED("GCExtendedGamepadSnapshot has been deprecated, use [GCController controllerWithExtendedGamepad] instead", macos(10.11, 10.15), ios(9.0, 13.0), tvos(9.0, 13.0));
#pragma pack(pop)

/**Fills out a snapshot from any compatible NSData source
 
 @return NO if data is nil, snapshotData is nil or the contents of data does not contain a compatible snapshot. YES for all other cases.
 */
BOOL GCExtendedGamepadSnapshotDataFromNSData(GCExtendedGamepadSnapshotData *__nullable snapshotData, NSData *__nullable data) API_DEPRECATED("GCExtendedGamepadSnapshot has been deprecated, use [GCController controllerWithExtendedGamepad] instead", macos(10.11, 10.15), ios(9.0, 13.0), tvos(9.0, 13.0));

/**Creates an NSData object from a snapshot.
 If the version and size is not set in the snapshot the data will automatically have the version GCCurrentExtendedGamepadSnapshotDataVersion and sizeof(GCExtendedGamepadSnapshotData) set as the values implicitly.
 
 @return nil if the snapshot is NULL, otherwise an NSData instance compatible with GCExtendedGamepadSnapshot.snapshotData
 */
NSData *__nullable NSDataFromGCExtendedGamepadSnapshotData(GCExtendedGamepadSnapshotData *__nullable snapshotData) API_DEPRECATED("GCExtendedGamepadSnapshot has been deprecated, use [GCController controllerWithExtendedGamepad] instead", macos(10.11, 10.15), ios(9.0, 13.0), tvos(9.0, 13.0));


#pragma mark - Deprecated Versioning System

#pragma pack(push)
typedef struct {
    // Standard information
    uint16_t version;   // 0x0100
    uint16_t size;      //sizeof(GCExtendedGamepadSnapShotDataV100) or larger
    
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
    
} GCExtendedGamepadSnapShotDataV100 API_DEPRECATED("GCExtendedGamepadSnapshot has been deprecated, use [GCController controllerWithExtendedGamepad] instead", macos(10.11, 10.15), ios(9.0, 13.0), tvos(9.0, 13.0));
#pragma pack(pop)

/**Fills out a v100 snapshot from any compatible NSData source
 
 @return NO if data is nil, snapshotData is nil or the contents of data does not contain a compatible snapshot. YES for all other cases.
 */
BOOL GCExtendedGamepadSnapShotDataV100FromNSData(GCExtendedGamepadSnapShotDataV100 *__nullable snapshotData, NSData *__nullable data) API_DEPRECATED("GCExtendedGamepadSnapshot has been deprecated, use [GCController controllerWithExtendedGamepad] instead", macos(10.11, 10.15), ios(9.0, 13.0), tvos(9.0, 13.0));

/**Creates an NSData object from a v100 snapshot.
 If the version and size is not set in the snapshot the data will automatically have version 0x100 and sizeof(GCExtendedGamepadSnapShotDataV100) set as the values implicitly.
 
 @return nil if the snapshot is NULL, otherwise an NSData instance compatible with GCExtendedGamepadSnapshot.snapshotData
 */
NSData *__nullable NSDataFromGCExtendedGamepadSnapShotDataV100(GCExtendedGamepadSnapShotDataV100 *__nullable snapshotData) API_DEPRECATED("GCExtendedGamepadSnapshot has been deprecated, use [GCController controllerWithExtendedGamepad] instead", macos(10.11, 10.15), ios(9.0, 13.0), tvos(9.0, 13.0));
NS_ASSUME_NONNULL_END
// ==========  GameController.framework/Headers/GCControllerButtonInput.h
//
//  GCControllerButtonInput.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

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
@property (nonatomic, copy, nullable) GCControllerButtonValueChangedHandler pressedChangedHandler API_AVAILABLE(macos(10.10), ios(8.0), tvos(8.0));

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

/**
 Sets the normalized value for the button input. Will update the pressed state of the button.

 @param value the value to set the input to.
 @note If the controller's snapshot flag is set to NO, this method has no effect.
 @see value
 */
- (void)setValue:(float)value;

@end

NS_ASSUME_NONNULL_END

// ==========  GameController.framework/Headers/GCGamepad.h
//
//  GCGamepad.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameController/GCExtern.h>

NS_ASSUME_NONNULL_BEGIN

@class GCController;
@class GCGamepadSnapshot;
@class GCControllerDirectionPad;
@class GCControllerElement;
@class GCControllerButtonInput;

/**
 Standard Gamepad profile.
 
 All controller profiles provide a base level of information about the controller they belong to.
 
 A profile maps the hardware notion of a controller into a logical controller. One that a developer can design for
 and depend on, no matter the underlying hardware.
 */

API_DEPRECATED_WITH_REPLACEMENT("GCExtendedGamepad", macos(10.9, 10.12), ios(7.0, 10.0), tvos(7.0, 10.0))
@interface GCGamepad : NSObject

/**
 A profile keeps a reference to the controller that this profile is mapping input from.
 */
@property (nonatomic, readonly, weak) GCController *controller;

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
// ==========  GameController.framework/Headers/GCRay.h
//
//  GCRay.h
//  CoreController
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

GAMECONTROLLER_EXPORT
@interface GCRay : NSObject

- (id)initWithOrigin:(simd_float3)origin direction:(simd_float3)direction;

@property (nonatomic, assign) simd_float3 origin;
@property (nonatomic, assign) simd_float3 direction; // normalized direction vector

@end

NS_ASSUME_NONNULL_END
// ==========  GameController.framework/Headers/GCEventViewController.h
//
//  GCEventViewController.h
//  CoreController
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#if TARGET_OS_IPHONE
#import <UIKit/UIViewController.h>
#else
#import <AppKit/NSViewController.h>
#endif

/**
 A view controller subclass that allows fine grained control of the user interface system's handling
 of game controller events. Set an instance of this class as your root view controller if you intend
 to use GCController APIs for handling game controllers.
 */
#if TARGET_OS_IPHONE
API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
@interface GCEventViewController : UIViewController
#else
API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
@interface GCEventViewController : NSViewController
#endif

/**
 Controllers can be used to control the general UIKit user interface and for many views that is
 the default behavior. By using a controller event view controller you get fine grained control
 over whether the controller events go trough the UIEvent & UIResponder chain, or if they are
 decoupled from the UI and all incoming data is served via GCController.
 
 Defaults to NO - suppressing UIEvents from game controllers and presenting them via the GCController
 API whilst this controller's view or any of it's subviews are the first responders. If you are not
 using any UIView components or UIEvents in your application you should leave this as NO and process
 your game controller events via the normal GCController API.
 
 If set to YES the controller input will start flowing through UIEvent and the UIResponder
 chain will be used. This gives you fine grained control over the event handling of the
 controlled view and its subviews. You should stop using GCController instances and the corresponding
 profiles if you no longer need to read input from them.
 
 Note that unlike UIView.userInteractionEnabled this only controls the flow of game controller events.
 
 @see GCController
 @see UIView.userInteractionEnabled
 */
@property (nonatomic, assign) BOOL controllerUserInteractionEnabled;

@end
// ==========  GameController.framework/Headers/GCExtendedGamepad.h
//
//  GCExtendedGamepad.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameController/GCExtern.h>

NS_ASSUME_NONNULL_BEGIN

@class GCController;
@class GCExtendedGamepadSnapshot;
@class GCControllerDirectionPad;
@class GCControllerElement;
@class GCControllerButtonInput;

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
- (GCExtendedGamepadSnapshot *)saveSnapshot API_DEPRECATED("GCExtendedGamepadSnapshot has been deprecated, use [GCController capture] instead", macos(10.9, 10.15), ios(7.0, 13.0), tvos(7.0, 13.0));

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
 Button menu is the primary menu button, and should be used to enter the main menu and pause the game.
 */
@property (nonatomic, readonly) GCControllerButtonInput *buttonMenu API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

/**
 Button options is the secondary menu button. It should be used to enter a secondary menu, such as graphics and sound configuration, and pause the game.
 */
@property (nonatomic, readonly, nullable) GCControllerButtonInput *buttonOptions API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

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

/**
 A thumbstick may also have a clickable component, which is treated as a non-analog button.
 */
@property (nonatomic, readonly, nullable) GCControllerButtonInput *leftThumbstickButton API_AVAILABLE(macos(10.14.1), ios(12.1), tvos(12.1));
@property (nonatomic, readonly, nullable) GCControllerButtonInput *rightThumbstickButton API_AVAILABLE(macos(10.14.1), ios(12.1), tvos(12.1));

/**
 Sets the state vector of the extended gamepad to a copy of the input extended gamepad's state vector.
 
 @note If the controller's snapshot flag is set to NO, this method has no effect.
 @see GCController.snapshot
 */
- (void) setStateFromExtendedGamepad:(GCExtendedGamepad *)extendedGamepad API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

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
 application to implement controller input replays. It is also returned as the result API_DEPRECATED("GCGamepad has been deprecated, use GCExtendedGamepad instead", macos(10.9, 10.15), ios(7.0, 13.0), tvos(7.0, 13.0))of polling
 a controller.
 
 The current snapshotData is readily available to access as NSData. A developer can serialize this to any
 destination necessary using the NSData API.
 
 The data contains some version of a GCGamepadSnapShotData structure.
 
 @see -[GCGamepad saveSnapshot]
 */
API_DEPRECATED("GCGamepad has been deprecated, use GCExtendedGamepad instead", macos(10.9, 10.15), ios(7.0, 13.0), tvos(7.0, 13.0))
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
    
} GCGamepadSnapShotDataV100 API_DEPRECATED("GCGamepad has been deprecated, use GCExtendedGamepad instead", macos(10.9, 10.15), ios(7.0, 13.0), tvos(7.0, 13.0));
#pragma pack(pop)

/**Fills out a v100 snapshot from any compatible NSData source
 
 @return NO if data is nil, snapshotData is nil or the contents of data does not contain a compatible snapshot. YES for all other cases.
 */
BOOL GCGamepadSnapShotDataV100FromNSData(GCGamepadSnapShotDataV100 *__nullable snapshotData, NSData *__nullable data) API_DEPRECATED("GCGamepad has been deprecated, use GCExtendedGamepad instead", macos(10.9, 10.15), ios(7.0, 13.0), tvos(7.0, 13.0));

/**Creates an NSData object from a v100 snapshot.
 If the version and size is not set in the snapshot the data will automatically have version 0x100 and sizeof(GCGamepadSnapShotDataV100) set as the values implicitly.
 
 @return nil if the snapshot is NULL, otherwise an NSData instance compatible with GCGamepadSnapshot.snapshotData
 */
NSData *__nullable NSDataFromGCGamepadSnapShotDataV100(GCGamepadSnapShotDataV100 *__nullable snapshotData) API_DEPRECATED("GCGamepad has been deprecated, use GCExtendedGamepad instead", macos(10.9, 10.15), ios(7.0, 13.0), tvos(7.0, 13.0));

NS_ASSUME_NONNULL_END
// ==========  GameController.framework/Headers/GCControllerAxisInput.h
//
//  GCControllerAxisInput.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <GameController/GameController.h>
#import <GameController/GCExtern.h>

NS_ASSUME_NONNULL_BEGIN

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

/**
 Sets the normalized value for the input.
 
 @param value the value to set the input to.
 @note If the controller's snapshot flag is set to NO, this method has no effect.
 @see value
 */
- (void)setValue:(float)value;

@end

NS_ASSUME_NONNULL_END

// ==========  GameController.framework/Headers/GCControllerDirectionPad.h
//
//  GCControllerDirectionPad.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <GameController/GameController.h>

@class GCControllerAxisInput;
@class GCControllerButtonInput;

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

/**
 Sets the normalized value for the direction pad's axis inputs. Will update the states of the direction pad's button inputs as well.
 
 @param xAxis the value to set the xAxis of the touchpad to.
 @param yAxis the value to set the yAxis of the touchpad to.
 @note If the controller's snapshot flag is set to NO, this method has no effect.
 @see value
 @see pressed
 */
- (void)setValueForXAxis:(float)xAxis yAxis:(float)yAxis;

@end

NS_ASSUME_NONNULL_END
// ==========  GameController.framework/Headers/GCExtern.h
//
//  GCExtern.h
//  GameController
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#ifdef __cplusplus
#define GAMECONTROLLER_EXTERN		extern "C" __attribute__((visibility ("default")))
#else
#define GAMECONTROLLER_EXTERN	        extern __attribute__((visibility ("default")))
#endif

#define GAMECONTROLLER_EXPORT API_AVAILABLE(macos(10.9), ios(7.0), tvos(7.0))
// ==========  GameController.framework/Headers/GCMicroGamepadSnapshot.h
//
//  GCMicroGamepadSnapshot.h
//  GameController
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <GameController/GameController.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A GCMicroGamepadSnapshot snapshot is a concrete GCMicroGamepad implementation. It can be used directly in an
 application to implement controller input replays. It is also returned as the result of polling
 a controller.
 
 The current snapshotData is readily available to access as NSData. A developer can serialize this to any
 destination necessary using the NSData API.
 
 The data contains some version of a GCMicroGamepadSnapShotData structure.
 
 @see -[GCMicroGamepad saveSnapshot]
 */
API_DEPRECATED("GCMicroGamepadSnapshot has been deprecated, use [GCController controllerWithMicroGamepad] instead", macos(10.11, 10.15), ios(9.0, 13.0), tvos(9.0, 13.0))
@interface GCMicroGamepadSnapshot : GCMicroGamepad
@property (atomic, copy) NSData *snapshotData;

- (instancetype)initWithSnapshotData:(NSData *)data;
- (instancetype)initWithController:(GCController *)controller snapshotData:(NSData *)data;

@end

typedef NS_ENUM(NSInteger, GCMicroGamepadSnapshotDataVersion) {
    GCMicroGamepadSnapshotDataVersion1 = 0x0100
} API_DEPRECATED("GCMicroGamepadSnapshot has been deprecated, use [GCController controllerWithMicroGamepad] instead", macos(10.11, 10.15), ios(9.0, 13.0), tvos(9.0, 13.0));

extern const GCMicroGamepadSnapshotDataVersion GCCurrentMicroGamepadSnapshotDataVersion API_DEPRECATED("GCMicroGamepadSnapshot has been deprecated, use [GCController controllerWithMicroGamepad] instead", macos(10.11, 10.15), ios(9.0, 13.0), tvos(9.0, 13.0));

#pragma pack(push, 1)
typedef struct {
    
#pragma mark - GCMicroGamepadSnapshotDataVersion1+
    uint16_t version;
    uint16_t size;
    
    // Standard gamepad data
    // Axes in the range [-1.0, 1.0]
    float dpadX;
    float dpadY;
    
    // Buttons in the range [0.0, 1.0]
    float buttonA;
    float buttonX;
    
} GCMicroGamepadSnapshotData API_DEPRECATED("GCMicroGamepadSnapshot has been deprecated, use [GCController controllerWithMicroGamepad] instead", macos(10.11, 10.15), ios(9.0, 13.0), tvos(9.0, 13.0));
#pragma pack(pop)

/**Fills out a snapshot from any compatible NSData source
 
 @return NO if data is nil, snapshotData is nil or the contents of data does not contain a compatible snapshot. YES for all other cases.
 */
BOOL GCMicroGamepadSnapshotDataFromNSData(GCMicroGamepadSnapshotData *__nullable snapshotData, NSData *__nullable data) API_DEPRECATED("GCMicroGamepadSnapshot has been deprecated, use [GCController controllerWithMicroGamepad] instead", macos(10.11, 10.15), ios(9.0, 13.0), tvos(9.0, 13.0));

/**Creates an NSData object from a snapshot.
 If the version and size is not set in the snapshot the data will automatically have version GCCurrentMicroGamepadSnapshotDataVersion and sizeof(GCMicroGamepadSnapshotData) set as the values implicitly.
 
 @return nil if the snapshot is NULL, otherwise an NSData instance compatible with GCGamepadSnapshot.snapshotData
 */
NSData *__nullable NSDataFromGCMicroGamepadSnapshotData(GCMicroGamepadSnapshotData *__nullable snapshotData) API_DEPRECATED("GCMicroGamepadSnapshot has been deprecated, use [GCController controllerWithMicroGamepad] instead", macos(10.11, 10.15), ios(9.0, 13.0), tvos(9.0, 13.0));



#pragma mark - Deprecated Versioning System

#pragma pack(push, 1)
typedef struct {
    // Standard information
    uint16_t version; //0x0100
    uint16_t size;    //sizeof(GCMicroGamepadSnapShotDataV100) or larger
    
    // Standard gamepad data
    // Axes in the range [-1.0, 1.0]
    float dpadX;
    float dpadY;
    
    // Buttons in the range [0.0, 1.0]
    float buttonA;
    float buttonX;
    
} GCMicroGamepadSnapShotDataV100 API_DEPRECATED("GCMicroGamepadSnapshot has been deprecated, use [GCController controllerWithMicroGamepad] instead", macos(10.11, 10.15), ios(9.0, 13.0), tvos(9.0, 13.0));
#pragma pack(pop)

/**Fills out a v100 snapshot from any compatible NSData source
 
 @return NO if data is nil, snapshotData is nil or the contents of data does not contain a compatible snapshot. YES for all other cases.
 */
BOOL GCMicroGamepadSnapShotDataV100FromNSData(GCMicroGamepadSnapShotDataV100 *__nullable snapshotData, NSData *__nullable data) API_DEPRECATED("GCMicroGamepadSnapshot has been deprecated, use [GCController controllerWithMicroGamepad] instead", macos(10.11, 10.15), ios(9.0, 13.0), tvos(9.0, 13.0));

/**Creates an NSData object from a v100 snapshot.
 If the version and size is not set in the snapshot the data will automatically have version 0x100 and sizeof(GCMicroGamepadSnapShotDataV100) set as the values implicitly.
 
 @return nil if the snapshot is NULL, otherwise an NSData instance compatible with GCGamepadSnapshot.snapshotData
 */
NSData *__nullable NSDataFromGCMicroGamepadSnapShotDataV100(GCMicroGamepadSnapShotDataV100 *__nullable snapshotData) API_DEPRECATED("GCMicroGamepadSnapshot has been deprecated, use [GCController controllerWithMicroGamepad] instead", macos(10.11, 10.15), ios(9.0, 13.0), tvos(9.0, 13.0));

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

#import <GameController/GCExtern.h>
#import <GameController/GCRay.h>

#import <GameController/GCControllerElement.h>
#import <GameController/GCControllerAxisInput.h>
#import <GameController/GCControllerButtonInput.h>
#import <GameController/GCControllerDirectionPad.h>

#import <GameController/GCMotion.h>

#import <GameController/GCGamepad.h>
#import <GameController/GCGamepadSnapshot.h>

#import <GameController/GCExtendedGamepad.h>
#import <GameController/GCExtendedGamepadSnapshot.h>

#import <GameController/GCMicroGamepad.h>
#import <GameController/GCMicroGamepadSnapshot.h>


#import <GameController/GCController.h>
#import <GameController/GCEventViewController.h>
// ==========  GameController.framework/Headers/GCController.h
//
//  GCController.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameController/GameController.h>
#import <GameController/GCExtern.h>

@class GCMotion;

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
 of suspension in play. You may pause and resume based on game state as well so the event is only called each time the
 pause/resume button is pressed.
 
 @note This handler has been deprecated in favor of the Menu button found on GCMicroGamepad and GCExtendedGamepad.
 @see microGamepad
 @see extendedGamepad
 */
@property (nonatomic, copy, nullable) void (^controllerPausedHandler)(GCController *controller) API_DEPRECATED("controllerPausedHandler has been deprecated. Use the Menu button found on the controller's profile, if it exists.", macos(10.9, 10.15), ios(7.0, 13.0), tvos(9.0, 13.0));

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
@property (nonatomic, retain) dispatch_queue_t handlerQueue;
#else
@property (nonatomic, assign) dispatch_queue_t handlerQueue;
#endif

/**
 A vendor supplied name. May be nil, and is not guaranteed to be unique. This should not be used as a key in a dictionary,
 but simply as a way to present some basic information about the controller in testing or to the user.
 */
@property (nonatomic, readonly, copy, nullable) NSString *vendorName;

/**
 The product category the controller belongs to. This is useful for setting appropriate UI elements based on what type of controller is connected.
 */
@property (nonatomic, readonly) NSString * productCategory API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

/**
 A controller may be form fitting or otherwise closely attached to the device. This closeness to other inputs on the device
 may suggest that interaction with the device may use other inputs easily. This is presented to developers to allow them to
 make informed decisions about UI and interactions to choose for their game in this situation.
 */
@property (nonatomic, readonly, getter = isAttachedToDevice) BOOL attachedToDevice;

/**
 A controller may represent a real device managed by the operating system, or a virtual snapshot created by the developer.
 If a controller is directly created by the developer, it is considered to be a snapshot, allowing direct writes to any
 GCControllerElement of its profiles. If the controller is not snapshot, the system will reject any write requests to GCControllerElement.
 
 @see controllerWithMicroGamepad
 @see controllerWithExtendedGamepad
 @see capture
 */
@property (atomic, readonly, getter = isSnapshot) BOOL snapshot API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

/**
 A player index for the controller, defaults to GCControllerPlayerIndexUnset.
 
 This can be set both for the application to keep track of controllers and as a signal to make a controller display a player
 index on a set of LEDs or some other mechanism.
 
 A controller is not guranteed to have a visual display of the playerIndex, playerIndex does not persist for a controller
 with regards to a system.
 
 Negative values less than GCControllerPlayerIndexUnset will just map back to GCControllerPlayerIndexUnset when read back.
 */
@property (nonatomic) GCControllerPlayerIndex playerIndex;

/**
 Gets the profile for the controller that suits current application.
 
 There are several supported profiles, with an additional optional profile for motion as well.
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
@property (nonatomic, retain, readonly, nullable) GCGamepad *gamepad API_DEPRECATED_WITH_REPLACEMENT("-extendedGamepad", macos(10.9, 10.12), ios(7.0, 10.0), tvos(7.0, 10.0));
@property (nonatomic, retain, readonly, nullable) GCMicroGamepad *microGamepad;
@property (nonatomic, retain, readonly, nullable) GCExtendedGamepad *extendedGamepad;

/**
 Gets the motion input profile. This profile is optional and may be available if the controller is attached to a device that supports motion.
 If this is nil the controller does not support motion input and only the gamepad & extendedGamepad profiles are available.
 @see gamepad
 @see extendedGamepad
 */
@property (nonatomic, retain, readonly, nullable) GCMotion *motion API_AVAILABLE(macos(10.10), ios(8.0), tvos(8.0));

/**
 Polls the state vector of the controller and saves it to a new and writable instance of GCController.
 
 If your application is heavily multithreaded this may also be useful to guarantee atomicity of input handling as
 a snapshot will not change based on user input once it is taken.
 
 @see snapshot
 @return A new controller with the duplicated state vector of the current controller
 */
- (GCController *) capture API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

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

/**
 Creates a controller with a micro gamepad profile.
 
 This controller will be considered a snapshot, allowing developers to write to any GCControllerElement of its profiles.
 
 @see snapshot
 @return A new controller with a micro gamepad profile
 */
+ (GCController *) controllerWithMicroGamepad API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

/**
 Creates a controller with an extended gamepad profile.
 
 This controller will be considered a snapshot, allowing developers to write to any GCControllerElement of its profiles.
 
 @see snapshot
 @return A new controller with an extended gamepad profile
 */
+ (GCController *) controllerWithExtendedGamepad API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));


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
API_AVAILABLE(macos(10.9), ios(7.0), tvos(7.0))
@interface GCControllerElement : NSObject

/**
 Each element can be part of a wider collection of inputs that map to a single logical element. A directional pad (dpad)
 is a logical collection of two axis inputs and thus each axis belongs to the same collection element - the dpad.
 */
@property (nonatomic, weak, readonly, nullable) GCControllerElement *collection;

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

#import <Foundation/Foundation.h>

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
API_AVAILABLE(macos(10.10), ios(8.0), tvos(8.0))
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
 The controller generating the motion data has sensors that can accurately determine the current attitude and rotation rate. If this is enabled the motion data for attitude and rotation rate are usable for inputs.
 */
@property (nonatomic, assign, readonly) BOOL hasAttitudeAndRotationRate API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

/**
 The current attitude of the controller.
 
 @note Remotes without accurate attitude and rotation rate can not determine a stable attitude so the values will be (0,0,0,1) at all times.
 @see hasAttitudeAndRotationRate
 @see GCMicroGamepad
 */
@property (nonatomic, assign, readonly) GCQuaternion attitude API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

/**
 The current rotation rate of the controller.
 
 @note Remotes without accurate attitude and rotation rate can not determine a stable rotation rate so the values will be (0,0,0) at all times.
 @see hasAttitudeAndRotationRate
 @see GCMicroGamepad
 */
@property (nonatomic, assign, readonly) GCRotationRate rotationRate API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

/**
 Sets the gravity vector expressed in the controller's reference frame.
 
 @note If the controller's snapshot flag is set to NO, this method has no effect.
 @see gravity
 */
- (void)setGravity:(GCAcceleration)gravity API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

/**
 Sets the acceleration that the user is giving to the controller.
 
 @note If the controller's snapshot flag is set to NO, this method has no effect.
 @see userAcceleration
 */
- (void)setUserAcceleration:(GCAcceleration)userAcceleration API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

/**
 Sets the current rotation rate of the controller.
 
 @note If the controller's snapshot flag is set to NO, this method has no effect.
 @see attitude
 */
- (void)setAttitude:(GCQuaternion)attitude API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

/**
 Sets the current rotation rate of the controller.
 
 @note If the controller's snapshot flag is set to NO, this method has no effect.
 @see rotationRate
 */
- (void)setRotationRate:(GCRotationRate)rotationRate API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

/**
 Sets the state vector of the motion profile to a copy of the input motion profile's state vector.
 
 @note If the controller's snapshot flag is set to NO, this method has no effect.
 @see GCController.snapshot
 */
- (void) setStateFromMotion:(GCMotion *)motion API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

@end

NS_ASSUME_NONNULL_END
// ==========  GameController.framework/Headers/GCMicroGamepad.h
//
//  GCMicroGamepad.h
//  GameController
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameController/GCExtern.h>

NS_ASSUME_NONNULL_BEGIN

@class GCController;
@class GCMicroGamepadSnapshot;
@class GCControllerDirectionPad;
@class GCControllerElement;
@class GCControllerButtonInput;

/**
 Micro Gamepad profile.
 
 All controller profiles provide a base level of information about the controller they belong to.
 
 A profile maps the hardware notion of a controller into a logical controller. One that a developer can design for
 and depend on, no matter the underlying hardware.
 */
API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
@interface GCMicroGamepad : NSObject

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
typedef void (^GCMicroGamepadValueChangedHandler)(GCMicroGamepad *gamepad, GCControllerElement *element);
@property (nonatomic, copy, nullable) GCMicroGamepadValueChangedHandler valueChangedHandler;

/**
 Polls the state vector of the controller and saves it to a snapshot. The snapshot is stored in a device independent
 format that can be serialized and used at a later date. This is useful for features such as quality assurance,
 save game or replay functionality among many.
 
 If your application is heavily multithreaded this may also be useful to guarantee atomicity of input handling as
 a snapshot will not change based on user input once it is taken.
 
 @see GCMicroGamepadSnapshot
 */
- (GCMicroGamepadSnapshot *)saveSnapshot API_DEPRECATED("GCMicroGamepadSnapshot has been deprecated, use [GCController capture] instead", macos(10.9, 10.15), ios(7.0, 13.0), tvos(7.0, 13.0));

/**
 Optionally analog in the Micro profile. All the elements of this directional input are either analog or digital.
 */
@property (nonatomic, readonly, retain) GCControllerDirectionPad *dpad;

/**
 The Micro profile has two buttons that are optionally analog in the Micro profile.
 Button A is the primary action button, it indicates affirmative action and should be used to advance in menus
 or perform the primary action in gameplay.
 */
@property (nonatomic, readonly, retain) GCControllerButtonInput *buttonA;

/**
 Button X is the secondary action button, it indicates an alternate affirmative action and should be used to perform
 a secondary action. If there is no secondary action it should be used as equivalent to buttonA.
 
 Unlike on other profiles there is no negative button on this profile. Instead the menu button should be
 used to present menu content or to retreat in a menu flow.
 @see buttonA
 */
@property (nonatomic, readonly, retain) GCControllerButtonInput *buttonX;

/**
 Button menu is the primary menu button, and should be used to enter the main menu and pause the game.
 */
@property (nonatomic, readonly) GCControllerButtonInput *buttonMenu API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

/**
 The Micro profile can use the raw position values of the touchpad on the remote as D-pad values, or it can create a virtual dpad centered around the first contact point with the surface.
 
 If NO; a smaller sliding window is created around the initial touch point and subsequent movement is relative to that center. Movement outside the window will slide the window with it to re-center it. This is great for surfaces where there is no clear sense of a middle and drift over time is an issue.
 
 If YES; the absolute values are used and any drift will have to managed manually either through user traning or by a developer using the dpad.
 
 The default value for this property is NO, meaning a sliding window is used for the dpad.
 */
@property (nonatomic, assign) BOOL reportsAbsoluteDpadValues;

/**
 Allows the Micro profile to monitor the orientation of the controller, if the controller is positioned in landscape orientation, D-pad input values will be transposed 90 degrees to match the new orientation.
 
 The default value for this property is NO.
 */
@property (nonatomic, assign) BOOL allowsRotation;

/**
 Sets the state vector of the micro gamepad to a copy of the input micro gamepad's state vector.
 
 @note If the controller's snapshot flag is set to NO, this method has no effect.
 @see GCController.snapshot
 */
- (void) setStateFromMicroGamepad:(GCMicroGamepad *)microGamepad API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));

@end


NS_ASSUME_NONNULL_END
