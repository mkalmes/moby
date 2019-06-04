// ==========  PencilKit.framework/Headers/PKInkingTool.h
//
//  PKInkingTool.h
//  PencilKit
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <PencilKit/PencilKit.h>
#import <PencilKit/PKTool.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif

NS_ASSUME_NONNULL_BEGIN

typedef NSString * PKInkType NS_TYPED_ENUM NS_REFINED_FOR_SWIFT;
FOUNDATION_EXPORT PKInkType const PKInkTypePen;
FOUNDATION_EXPORT PKInkType const PKInkTypePencil;
FOUNDATION_EXPORT PKInkType const PKInkTypeMarker;


/// A tool for drawing on a PKCanvasView.
NS_REFINED_FOR_SWIFT
@interface PKInkingTool : PKTool

/// Create a new ink, specifying its type, color, and width.
///
/// @param type The type of ink.
/// @param color The color of the ink.
/// @param width The width of the ink.
#if TARGET_OS_IPHONE
- (instancetype)initWithInkType:(PKInkType)type color:(UIColor *)color width:(CGFloat)width NS_DESIGNATED_INITIALIZER;
#else
- (instancetype)initWithInkType:(PKInkType)type color:(NSColor *)color width:(CGFloat)width NS_DESIGNATED_INITIALIZER;
#endif
/// Create a new ink, specifying its type and color, using a default width.
///
/// @param type The type of ink.
/// @param color The color of the ink.
#if TARGET_OS_IPHONE
- (instancetype)initWithInkType:(PKInkType)type color:(UIColor *)color;
#else
- (instancetype)initWithInkType:(PKInkType)type color:(NSColor *)color;
#endif

/// The default width for an ink of a type.
+ (CGFloat)defaultWidthForInkType:(PKInkType)inkType;

/// The minimum width for an ink of a type.
+ (CGFloat)minimumWidthForInkType:(PKInkType)inkType;

/// The maximum width for an ink of a type.
+ (CGFloat)maximumWidthForInkType:(PKInkType)inkType;

/// The type of ink, eg. pen, pencil...
@property (nonatomic, readonly) PKInkType inkType;

/// The base color of this ink.
#if TARGET_OS_IPHONE
@property (nonatomic, readonly) UIColor *color;
#else
@property (nonatomic, readonly) NSColor *color;
#endif

/// The base width of the ink.
@property (nonatomic, readonly) CGFloat width;

@end
NS_ASSUME_NONNULL_END
// ==========  PencilKit.framework/Headers/PKToolPicker.h
//
//  PKToolPicker.h
//  PencilKit
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class PKTool, PKToolPicker;

@protocol PKToolPickerObserver <NSObject>

@optional
/// Tells the delegate that the selected tool was changed by the user.
///
/// @param toolPicker  The tool picker that changed.
- (void)toolPickerSelectedToolDidChange:(PKToolPicker *)toolPicker;

/// Tells the delegate that the ruler active state was changed by the user.
///
/// @param toolPicker  The tool picker that changed.
- (void)toolPickerIsRulerActiveDidChange:(PKToolPicker *)toolPicker;

/// Tells the delegate that the tool picker UI changed visibility.
///
/// @param toolPicker  The tool picker that changed.
- (void)toolPickerVisibilityDidChange:(PKToolPicker *)toolPicker;

/// Tells the delegate that the frames the tool picker obscures changed.
/// Note, the obscured frames for a view can also change when that view
/// changes, not just when this delegate method is called.
///
/// @param toolPicker  The tool picker that changed.
- (void)toolPickerFramesObscuredDidChange:(PKToolPicker *)toolPicker;

@end


/// A user interface for selecting a PKTool.
@interface PKToolPicker : NSObject

/// Add an observer for a tool picker changes.
///
/// Adding a `PKCanvasView` as an observer, will also set its initial state.
/// Observers are held weakly.
- (void)addObserver:(id<PKToolPickerObserver>)observer NS_SWIFT_NAME(addObserver(_:));

/// Remove an observer for a tool picker changes.
- (void)removeObserver:(id<PKToolPickerObserver>)observer NS_SWIFT_NAME(removeObserver(_:));

/// Sets when this tool picker should be visible.
///
/// @param visible  The visible state of this tool picker.
/// @param responder  The first responder for which this visible state applies.
- (void)setVisible:(BOOL)visible forFirstResponder:(UIResponder *)responder;

/// The currently selected tool.
@property (nonatomic, strong) PKTool *selectedTool;

/// Is the ruler toggled such that it should be active on canvases.
@property (nonatomic, getter=isRulerActive) BOOL rulerActive;

/// Is the tool picker visible.
@property (nonatomic, readonly) BOOL isVisible;

/// The frame within a specific view that the tool picker covers.
///
/// @param view The view in which to return the frame to avoid.
/// @return The rect in `view` that the tool picker obscures. Will return
/// `CGRectNull` if no rect is obscured, or the tool picker is movable.
- (CGRect)frameObscuredInView:(UIView *)view;

/// Returns the shared `PKToolPicker` instance for a window.
/// The returned tool picker object is typically shared between window in the same UIWindowScene.
+ (nullable PKToolPicker *)sharedToolPickerForWindow:(UIWindow *)window NS_SWIFT_NAME(shared(for:));

- (instancetype)init NS_UNAVAILABLE;

@end
NS_ASSUME_NONNULL_END
// ==========  PencilKit.framework/Headers/PencilKit.h
//
//  PencilKit.h
//  PencilKit
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#import <PencilKit/PKCanvasView.h>
#import <PencilKit/PKTool.h>
#import <PencilKit/PKLassoTool.h>
#import <PencilKit/PKEraserTool.h>
#import <PencilKit/PKInkingTool.h>
#import <PencilKit/PKToolPicker.h>
#endif

#import <PencilKit/PKDrawing.h>
// ==========  PencilKit.framework/Headers/PKEraserTool.h
//
//  PKEraserTool.h
//  PencilKit
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <PencilKit/PencilKit.h>
#import <PencilKit/PKTool.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, PKEraserType) {
    PKEraserTypeVector,
    PKEraserTypeBitmap
} NS_REFINED_FOR_SWIFT;

/// An eraser tool for erasing parts of a drawing.
NS_REFINED_FOR_SWIFT
@interface PKEraserTool : PKTool

/// The eraser type.
@property (nonatomic, readonly) PKEraserType eraserType;

- (instancetype)initWithEraserType:(PKEraserType)eraserType NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
// ==========  PencilKit.framework/Headers/PKLassoTool.h
//
//  PKLassoTool.h
//  PencilKit
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <PencilKit/PencilKit.h>
#import <PencilKit/PKTool.h>

NS_ASSUME_NONNULL_BEGIN

/// A lasso tool for selection parts of a drawing.
NS_REFINED_FOR_SWIFT
@interface PKLassoTool : PKTool

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
// ==========  PencilKit.framework/Headers/PKTool.h
//
//  PKTool.h
//  PencilKit
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// An interaction behavior for a PKCanvasView.
/// Should not be subclassed outside of the PencilKit framework.
NS_REFINED_FOR_SWIFT
@interface PKTool : NSObject <NSCopying>

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  PencilKit.framework/Headers/PKCanvasView.h
//
//  PKCanvasView.h
//  PencilKit
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <PencilKit/PKToolPicker.h>


NS_ASSUME_NONNULL_BEGIN

@class PKDrawing, PKTool, PKCanvasView;

/// The optional methods a delegate can receive from editing-related changes
/// to a PKCanvasView.
@protocol PKCanvasViewDelegate<NSObject, UIScrollViewDelegate>
@optional
/// Called after the drawing on the canvas did change.
///
/// This may be called some time after the `canvasViewDidEndUsingTool:` delegate method.
/// For example, when using the Apple Pencil, pressure data is delayed from touch data, this
/// means that the user can stop drawing (`canvasViewDidEndUsingTool:` is called), but the
/// canvas view is still waiting for final pressure values; only when the final pressure values
/// are received is the drawing updated and this delegate method called.
///
/// It is also possible that this method is not called, if the drawing interaction is cancelled.
///
/// @param canvasView The canvas view that changed.
- (void)canvasViewDrawingDidChange:(PKCanvasView *)canvasView;

/// Called after setting `drawing` when the entire drawing is rendered and visible.
///
/// This method lets you know when the canvas view finishes rendering all of the currently
/// visible content. This can be used to delay showing the canvas view until all content is visible.
///
/// This is called every time the canvasView transitions from partially rendered to fully rendered,
/// including after setting the drawing, and after zooming or scrolling.
///
/// @param canvasView The canvas view that finished rendering.
- (void)canvasViewDidFinishRendering:(PKCanvasView *)canvasView;

/// Called when the user starts using a tool, eg. selecting, drawing, or erasing.
///
/// This does not include moving the ruler.
///
/// @param canvasView The canvas view that the user started interacting with.
- (void)canvasViewDidBeginUsingTool:(PKCanvasView *)canvasView  NS_SWIFT_NAME(canvasViewDidBeginUsingTool(_:));

/// Called when the user stops using a tool, eg. selecting, drawing, or erasing.
///
/// @param canvasView The canvas view that the user ended interacting with.
- (void)canvasViewDidEndUsingTool:(PKCanvasView *)canvasView NS_SWIFT_NAME(canvasViewDidEndUsingTool(_:));
@end


/// The view for interactively drawing, and non-interactively showing PKDrawing contents.
@interface PKCanvasView : UIScrollView <PKToolPickerObserver>

/// The delegate for drawing operations.
@property (nonatomic, weak, nullable) id<PKCanvasViewDelegate> delegate;

/// The drawing shown on this view.
@property (nonatomic, copy) PKDrawing *drawing;

/// The tool used to interact with the canvas.
/// Default is `[[PKInkingTool alloc] initWithType:PKInkTypePen color:UIColor.blackColor]`
@property (nonatomic, copy) PKTool *tool NS_REFINED_FOR_SWIFT;

/// Is the ruler shown on the canvas.
@property (nonatomic, getter=isRulerActive) BOOL rulerActive;

/// The gesture recognizer used to draw in the canvas.
@property (nonatomic, readonly) UIGestureRecognizer *drawingGestureRecognizer;

/// Is the finger allowed to draw in the canvas.
/// If false, only styluses will draw. If true, two-fingers are used to scroll.
/// Defaults to YES.
@property (nonatomic) BOOL allowsFingerDrawing;

@end

NS_ASSUME_NONNULL_END
// ==========  PencilKit.framework/Headers/PKDrawing.h
//
//  PKDrawing.h
//  PencilKit
//
//  Copyright © 2019 Apple. All rights reserved.
//

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif


NS_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif
/// The UTType for storing drawing data.
extern const CFStringRef PKAppleDrawingTypeIdentifier;
#ifdef __cplusplus
}
#endif

/// The data model object for storing drawing data created from PKCanvasView.
NS_REFINED_FOR_SWIFT
@interface PKDrawing : NSObject <NSCopying, NSSecureCoding>

/// Initializes and returns a blank drawing.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Initializes and returns the drawing with the specified data.
///
/// @param data The data containing the drawing data.
/// @param error If an error occurs, upon return the NSError object describes the error.
///   Set to NULL to ignore errors.
/// @return On success, an initialized PKDrawing object. If nil, the outError parameter
///   contains an NSError instance describing the problem.
- (nullable instancetype)initWithData:(NSData *)data error:(NSError * _Nullable *)error NS_DESIGNATED_INITIALIZER;

/// Generate a data representation of the drawing.
///
/// @return A NSData object containing a representation of the drawing.
- (NSData *)dataRepresentation;

/// The bounds of the drawing's contents, taking into account the rendered width of all content.
/// If these bounds are used to render an image with `imageFromRect:scale:`, no contents will be cropped.
@property (nonatomic, readonly) CGRect bounds;

/// Renders the drawing to an image.
///
/// @param rect The rect in the drawing to render.
/// @param scale The scale of image to render. If you specify a value of 0.0, the scale factor is set to the
/// scale factor of the device’s main screen.
/// @return A non-opaque image of this drawing with pixel dimensions `rect.size * scale`.
#if TARGET_OS_IPHONE
- (UIImage *)imageFromRect:(CGRect)rect scale:(CGFloat)scale;
#else
- (NSImage *)imageFromRect:(CGRect)rect scale:(CGFloat)scale;
#endif

/// Returns a new drawing with `transform` applied.
///
/// @param transform The transform to apply to this drawing.
/// @return A new copy of this drawing with `transform` applied.
- (PKDrawing *)drawingByApplyingTransform:(CGAffineTransform)transform;

/// Returns a new drawing by appending the contents of `drawing` on top of the receiver’s contents.
///
/// @param drawing The drawing to append.
/// @return A new copy of this drawing with `drawing` appended onto it.
- (PKDrawing *)drawingByAppendingDrawing:(PKDrawing *)drawing;

@end

NS_ASSUME_NONNULL_END
