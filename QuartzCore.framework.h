// ==========  QuartzCore.framework/Headers/CATransformLayer.h
/* CoreAnimation - CATransformLayer.h

   Copyright (c) 2006-2018, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CALayer.h>

NS_ASSUME_NONNULL_BEGIN

/* "Transform" layers are used to create true 3D layer hierarchies.
 *
 * Unlike normal layers, transform layers do not project (i.e. flatten)
 * their sublayers into the plane at Z=0. However due to this neither
 * do they support many features of the 2D compositing model:
 *
 * - only their sublayers are rendered (i.e. no background, contents,
 *   border)
 *
 * - filters, backgroundFilters, compositingFilter, mask, masksToBounds
 *   and shadow related properties are ignored (they all assume 2D
 *   image processing of the projected layer)
 *
 * - opacity is applied to each sublayer individually, i.e. the transform
 *   layer does not form a compositing group.
 *
 * Also, the -hitTest: method should never be called on transform
 * layers (they do not have a 2D coordinate space into which to map the
 * supplied point.) CALayer will pass over transform layers directly to
 * their sublayers, applying the effects of the transform layer's
 * geometry when hit-testing each sublayer. */

API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0))
@interface CATransformLayer : CALayer
@end

NS_ASSUME_NONNULL_END
// ==========  QuartzCore.framework/Headers/QuartzCore.h
/* QuartzCore.h

   Copyright (c) 2004-2018, Apple Inc.
   All rights reserved. */

#ifndef QUARTZCORE_H
#define QUARTZCORE_H

#include <QuartzCore/CoreAnimation.h>

#endif /* QUARTZCORE_H */
// ==========  QuartzCore.framework/Headers/CAScrollLayer.h
/* CoreAnimation - CAScrollLayer.h

   Copyright (c) 2006-2018, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CALayer.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString * CAScrollLayerScrollMode NS_TYPED_ENUM;

API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
@interface CAScrollLayer : CALayer

/* Changes the origin of the layer to point 'p'. */

- (void)scrollToPoint:(CGPoint)p;

/* Scroll the contents of the layer to ensure that rect 'r' is visible. */

- (void)scrollToRect:(CGRect)r;

/* Defines the axes in which the layer may be scrolled. Possible values
 * are `none', `vertically', `horizontally' or `both' (the default). */

@property(copy) CAScrollLayerScrollMode scrollMode;

@end

@interface CALayer (CALayerScrolling)

/* These methods search for the closest ancestor CAScrollLayer of the *
 * receiver, and then call either -scrollToPoint: or -scrollToRect: on
 * that layer with the specified geometry converted from the coordinate
 * space of the receiver to that of the found scroll layer. */

- (void)scrollPoint:(CGPoint)p;

- (void)scrollRectToVisible:(CGRect)r;

/* Returns the visible region of the receiver, in its own coordinate
 * space. The visible region is the area not clipped by the containing
 * scroll layer. */

@property(readonly) CGRect visibleRect;

@end

/* `scrollMode' values. */

CA_EXTERN CAScrollLayerScrollMode const kCAScrollNone
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAScrollLayerScrollMode const kCAScrollVertically
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAScrollLayerScrollMode const kCAScrollHorizontally
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAScrollLayerScrollMode const kCAScrollBoth
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

NS_ASSUME_NONNULL_END
// ==========  QuartzCore.framework/Headers/CALayer.h
/* CoreAnimation - CALayer.h

   Copyright (c) 2006-2018, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CAMediaTiming.h>
#import <QuartzCore/CATransform3D.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSNull.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>

@class NSEnumerator, CAAnimation, CALayerArray;
@protocol CAAction, CALayerDelegate;

NS_ASSUME_NONNULL_BEGIN

typedef NSString * CALayerContentsGravity NS_TYPED_ENUM;
typedef NSString * CALayerContentsFormat NS_TYPED_ENUM;
typedef NSString * CALayerContentsFilter NS_TYPED_ENUM;
typedef NSString * CALayerCornerCurve NS_TYPED_ENUM;

/* Bit definitions for `edgeAntialiasingMask' property. */

typedef NS_OPTIONS (unsigned int, CAEdgeAntialiasingMask)
{
  kCALayerLeftEdge      = 1U << 0,      /* Minimum X edge. */
  kCALayerRightEdge     = 1U << 1,      /* Maximum X edge. */
  kCALayerBottomEdge    = 1U << 2,      /* Minimum Y edge. */
  kCALayerTopEdge       = 1U << 3,      /* Maximum Y edge. */
};

/* Bit definitions for `maskedCorners' property. */

typedef NS_OPTIONS (NSUInteger, CACornerMask)
{
  kCALayerMinXMinYCorner = 1U << 0,
  kCALayerMaxXMinYCorner = 1U << 1,
  kCALayerMinXMaxYCorner = 1U << 2,
  kCALayerMaxXMaxYCorner = 1U << 3,
};

/** The base layer class. **/

API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
@interface CALayer : NSObject <NSSecureCoding, CAMediaTiming>
{
@private
  struct _CALayerIvars {
    int32_t refcount;
    uint32_t magic;
    void *layer;
#if TARGET_OS_MAC && !TARGET_RT_64_BIT
    void * _Nonnull unused1[8];
#endif
  } _attr;
}

/** Layer creation and initialization. **/

+ (instancetype)layer;

/* The designated initializer. */

- (instancetype)init;

/* This initializer is used by CoreAnimation to create shadow copies of
 * layers, e.g. for use as presentation layers. Subclasses can override
 * this method to copy their instance variables into the presentation
 * layer (subclasses should call the superclass afterwards). Calling this
 * method in any other situation will result in undefined behavior. */

- (instancetype)initWithLayer:(id)layer;

/* Returns a copy of the layer containing all properties as they were
 * at the start of the current transaction, with any active animations
 * applied. This gives a close approximation to the version of the layer
 * that is currently displayed. Returns nil if the layer has not yet
 * been committed.
 *
 * The effect of attempting to modify the returned layer in any way is
 * undefined.
 *
 * The `sublayers', `mask' and `superlayer' properties of the returned
 * layer return the presentation versions of these properties. This
 * carries through to read-only layer methods. E.g., calling -hitTest:
 * on the result of the -presentationLayer will query the presentation
 * values of the layer tree. */

- (nullable instancetype)presentationLayer;

/* When called on the result of the -presentationLayer method, returns
 * the underlying layer with the current model values. When called on a
 * non-presentation layer, returns the receiver. The result of calling
 * this method after the transaction that produced the presentation
 * layer has completed is undefined. */

- (instancetype)modelLayer;

/** Property methods. **/

/* CALayer implements the standard NSKeyValueCoding protocol for all
 * Objective C properties defined by the class and its subclasses. It
 * dynamically implements missing accessor methods for properties
 * declared by subclasses.
 *
 * When accessing properties via KVC whose values are not objects, the
 * standard KVC wrapping conventions are used, with extensions to
 * support the following types:
 *
 *      C Type                  Class
 *      ------                  -----
 *      CGPoint                 NSValue
 *      CGSize                  NSValue
 *      CGRect                  NSValue
 *      CGAffineTransform       NSValue
 *      CATransform3D           NSValue  */

/* Returns the default value of the named property, or nil if no
 * default value is known. Subclasses that override this method to
 * define default values for their own properties should call `super'
 * for unknown properties. */

+ (nullable id)defaultValueForKey:(NSString *)key;

/* Method for subclasses to override. Returning true for a given
 * property causes the layer's contents to be redrawn when the property
 * is changed (including when changed by an animation attached to the
 * layer). The default implementation returns NO. Subclasses should
 * call super for properties defined by the superclass. (For example,
 * do not try to return YES for properties implemented by CALayer,
 * doing will have undefined results.) */

+ (BOOL)needsDisplayForKey:(NSString *)key;

/* Called by the object's implementation of -encodeWithCoder:, returns
 * false if the named property should not be archived. The base
 * implementation returns YES. Subclasses should call super for
 * unknown properties. */

- (BOOL)shouldArchiveValueForKey:(NSString *)key;

/** Geometry and layer hierarchy properties. **/

/* The bounds of the layer. Defaults to CGRectZero. Animatable. */

@property CGRect bounds;

/* The position in the superlayer that the anchor point of the layer's
 * bounds rect is aligned to. Defaults to the zero point. Animatable. */

@property CGPoint position;

/* The Z component of the layer's position in its superlayer. Defaults
 * to zero. Animatable. */

@property CGFloat zPosition;

/* Defines the anchor point of the layer's bounds rect, as a point in
 * normalized layer coordinates - '(0, 0)' is the bottom left corner of
 * the bounds rect, '(1, 1)' is the top right corner. Defaults to
 * '(0.5, 0.5)', i.e. the center of the bounds rect. Animatable. */

@property CGPoint anchorPoint;

/* The Z component of the layer's anchor point (i.e. reference point for
 * position and transform). Defaults to zero. Animatable. */

@property CGFloat anchorPointZ;

/* A transform applied to the layer relative to the anchor point of its
 * bounds rect. Defaults to the identity transform. Animatable. */

@property CATransform3D transform;

/* Convenience methods for accessing the `transform' property as an
 * affine transform. */

- (CGAffineTransform)affineTransform;
- (void)setAffineTransform:(CGAffineTransform)m;

/* Unlike NSView, each Layer in the hierarchy has an implicit frame
 * rectangle, a function of the `position', `bounds', `anchorPoint',
 * and `transform' properties. When setting the frame the `position'
 * and `bounds.size' are changed to match the given frame. */

@property CGRect frame;

/* When true the layer and its sublayers are not displayed. Defaults to
 * NO. Animatable. */

@property(getter=isHidden) BOOL hidden;

/* When false layers facing away from the viewer are hidden from view.
 * Defaults to YES. Animatable. */

@property(getter=isDoubleSided) BOOL doubleSided;

/* Whether or not the geometry of the layer (and its sublayers) is
 * flipped vertically. Defaults to NO. Note that even when geometry is
 * flipped, image orientation remains the same (i.e. a CGImageRef
 * stored in the `contents' property will display the same with both
 * flipped=NO and flipped=YES, assuming no transform on the layer). */

@property(getter=isGeometryFlipped) BOOL geometryFlipped;

/* Returns true if the contents of the contents property of the layer
 * will be implicitly flipped when rendered in relation to the local
 * coordinate space (e.g. if there are an odd number of layers with
 * flippedGeometry=YES from the receiver up to and including the
 * implicit container of the root layer). Subclasses should not attempt
 * to redefine this method. When this method returns true the
 * CGContextRef object passed to -drawInContext: by the default
 * -display method will have been y- flipped (and rectangles passed to
 * -setNeedsDisplayInRect: will be similarly flipped). */

- (BOOL)contentsAreFlipped;

/* The receiver's superlayer object. Implicitly changed to match the
 * hierarchy described by the `sublayers' properties. */

@property(nullable, readonly) CALayer *superlayer;

/* Removes the layer from its superlayer, works both if the receiver is
 * in its superlayer's `sublayers' array or set as its `mask' value. */

- (void)removeFromSuperlayer;

/* The array of sublayers of this layer. The layers are listed in back
 * to front order. Defaults to nil. When setting the value of the
 * property, any newly added layers must have nil superlayers, otherwise
 * the behavior is undefined. Note that the returned array is not
 * guaranteed to retain its elements. */

@property(nullable, copy) NSArray<__kindof CALayer *> *sublayers;

/* Add 'layer' to the end of the receiver's sublayers array. If 'layer'
 * already has a superlayer, it will be removed before being added. */

- (void)addSublayer:(CALayer *)layer;

/* Insert 'layer' at position 'idx' in the receiver's sublayers array.
 * If 'layer' already has a superlayer, it will be removed before being
 * inserted. */

- (void)insertSublayer:(CALayer *)layer atIndex:(unsigned)idx;

/* Insert 'layer' either above or below the specified layer in the
 * receiver's sublayers array. If 'layer' already has a superlayer, it
 * will be removed before being inserted. */

- (void)insertSublayer:(CALayer *)layer below:(nullable CALayer *)sibling;
- (void)insertSublayer:(CALayer *)layer above:(nullable CALayer *)sibling;

/* Remove 'oldLayer' from the sublayers array of the receiver and insert
 * 'newLayer' if non-nil in its position. If the superlayer of 'oldLayer'
 * is not the receiver, the behavior is undefined. */

- (void)replaceSublayer:(CALayer *)oldLayer with:(CALayer *)newLayer;

/* A transform applied to each member of the `sublayers' array while
 * rendering its contents into the receiver's output. Typically used as
 * the projection matrix to add perspective and other viewing effects
 * into the model. Defaults to identity. Animatable. */

@property CATransform3D sublayerTransform;

/* A layer whose alpha channel is used as a mask to select between the
 * layer's background and the result of compositing the layer's
 * contents with its filtered background. Defaults to nil. When used as
 * a mask the layer's `compositingFilter' and `backgroundFilters'
 * properties are ignored. When setting the mask to a new layer, the
 * new layer must have a nil superlayer, otherwise the behavior is
 * undefined. Nested masks (mask layers with their own masks) are
 * unsupported. */

@property(nullable, strong) __kindof CALayer *mask;

/* When true an implicit mask matching the layer bounds is applied to
 * the layer (including the effects of the `cornerRadius' property). If
 * both `mask' and `masksToBounds' are non-nil the two masks are
 * multiplied to get the actual mask values. Defaults to NO.
 * Animatable. */

@property BOOL masksToBounds;

/** Mapping between layer coordinate and time spaces. **/

- (CGPoint)convertPoint:(CGPoint)p fromLayer:(nullable CALayer *)l;
- (CGPoint)convertPoint:(CGPoint)p toLayer:(nullable CALayer *)l;
- (CGRect)convertRect:(CGRect)r fromLayer:(nullable CALayer *)l;
- (CGRect)convertRect:(CGRect)r toLayer:(nullable CALayer *)l;

- (CFTimeInterval)convertTime:(CFTimeInterval)t fromLayer:(nullable CALayer *)l;
- (CFTimeInterval)convertTime:(CFTimeInterval)t toLayer:(nullable CALayer *)l;

/** Hit testing methods. **/

/* Returns the farthest descendant of the layer containing point 'p'.
 * Siblings are searched in top-to-bottom order. 'p' is defined to be
 * in the coordinate space of the receiver's nearest ancestor that
 * isn't a CATransformLayer (transform layers don't have a 2D
 * coordinate space in which the point could be specified). */

- (nullable __kindof CALayer *)hitTest:(CGPoint)p;

/* Returns true if the bounds of the layer contains point 'p'. */

- (BOOL)containsPoint:(CGPoint)p;

/** Layer content properties and methods. **/

/* An object providing the contents of the layer, typically a CGImageRef,
 * but may be something else. (For example, NSImage objects are
 * supported on Mac OS X 10.6 and later.) Default value is nil.
 * Animatable. */

@property(nullable, strong) id contents;

/* A rectangle in normalized image coordinates defining the
 * subrectangle of the `contents' property that will be drawn into the
 * layer. If pixels outside the unit rectangles are requested, the edge
 * pixels of the contents image will be extended outwards. If an empty
 * rectangle is provided, the results are undefined. Defaults to the
 * unit rectangle [0 0 1 1]. Animatable. */

@property CGRect contentsRect;

/* A string defining how the contents of the layer is mapped into its
 * bounds rect. Options are `center', `top', `bottom', `left',
 * `right', `topLeft', `topRight', `bottomLeft', `bottomRight',
 * `resize', `resizeAspect', `resizeAspectFill'. The default value is
 * `resize'. Note that "bottom" always means "Minimum Y" and "top"
 * always means "Maximum Y". */

@property(copy) CALayerContentsGravity contentsGravity;

/* Defines the scale factor applied to the contents of the layer. If
 * the physical size of the contents is '(w, h)' then the logical size
 * (i.e. for contentsGravity calculations) is defined as '(w /
 * contentsScale, h / contentsScale)'. Applies to both images provided
 * explicitly and content provided via -drawInContext: (i.e. if
 * contentsScale is two -drawInContext: will draw into a buffer twice
 * as large as the layer bounds). Defaults to one. Animatable. */

@property CGFloat contentsScale
  API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));

/* A rectangle in normalized image coordinates defining the scaled
 * center part of the `contents' image.
 *
 * When an image is resized due to its `contentsGravity' property its
 * center part implicitly defines the 3x3 grid that controls how the
 * image is scaled to its drawn size. The center part is stretched in
 * both dimensions; the top and bottom parts are only stretched
 * horizontally; the left and right parts are only stretched
 * vertically; the four corner parts are not stretched at all. (This is
 * often called "9-slice scaling".)
 *
 * The rectangle is interpreted after the effects of the `contentsRect'
 * property have been applied. It defaults to the unit rectangle [0 0 1
 * 1] meaning that the entire image is scaled. As a special case, if
 * the width or height is zero, it is implicitly adjusted to the width
 * or height of a single source pixel centered at that position. If the
 * rectangle extends outside the [0 0 1 1] unit rectangle the result is
 * undefined. Animatable. */

@property CGRect contentsCenter;

/* A hint for the desired storage format of the layer contents provided by
 * -drawLayerInContext. Defaults to kCAContentsFormatRGBA8Uint. Note that this
 * does not affect the interpretation of the `contents' property directly. */

@property(copy) CALayerContentsFormat contentsFormat
  API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/* The filter types to use when rendering the `contents' property of
 * the layer. The minification filter is used when to reduce the size
 * of image data, the magnification filter to increase the size of
 * image data. Currently the allowed values are `nearest' and `linear'.
 * Both properties default to `linear'. */

@property(copy) CALayerContentsFilter minificationFilter;
@property(copy) CALayerContentsFilter magnificationFilter;

/* The bias factor added when determining which levels of detail to use
 * when minifying using trilinear filtering. The default value is 0.
 * Animatable. */

@property float minificationFilterBias;

/* A hint marking that the layer contents provided by -drawInContext:
 * is completely opaque. Defaults to NO. Note that this does not affect
 * the interpretation of the `contents' property directly. */

@property(getter=isOpaque) BOOL opaque;

/* Reload the content of this layer. Calls the -drawInContext: method
 * then updates the `contents' property of the layer. Typically this is
 * not called directly. */

- (void)display;

/* Marks that -display needs to be called before the layer is next
 * committed. If a region is specified, only that region of the layer
 * is invalidated. */

- (void)setNeedsDisplay;
- (void)setNeedsDisplayInRect:(CGRect)r;

/* Returns true when the layer is marked as needing redrawing. */

- (BOOL)needsDisplay;

/* Call -display if receiver is marked as needing redrawing. */

- (void)displayIfNeeded;

/* When true -setNeedsDisplay will automatically be called when the
 * bounds of the layer changes. Default value is NO. */

@property BOOL needsDisplayOnBoundsChange;

/* When true, the CGContext object passed to the -drawInContext: method
 * may queue the drawing commands submitted to it, such that they will
 * be executed later (i.e. asynchronously to the execution of the
 * -drawInContext: method). This may allow the layer to complete its
 * drawing operations sooner than when executing synchronously. The
 * default value is NO. */

@property BOOL drawsAsynchronously
  API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

/* Called via the -display method when the `contents' property is being
 * updated. Default implementation does nothing. The context may be
 * clipped to protect valid layer content. Subclasses that wish to find
 * the actual region to draw can call CGContextGetClipBoundingBox(). */

- (void)drawInContext:(CGContextRef)ctx;

/** Rendering properties and methods. **/

/* Renders the receiver and its sublayers into 'ctx'. This method
 * renders directly from the layer tree. Renders in the coordinate space
 * of the layer.
 *
 * WARNING: currently this method does not implement the full
 * CoreAnimation composition model, use with caution. */

- (void)renderInContext:(CGContextRef)ctx;

/* Defines how the edges of the layer are rasterized. For each of the
 * four edges (left, right, bottom, top) if the corresponding bit is
 * set the edge will be antialiased. Typically this property is used to
 * disable antialiasing for edges that abut edges of other layers, to
 * eliminate the seams that would otherwise occur. The default value is
 * for all edges to be antialiased. */

@property CAEdgeAntialiasingMask edgeAntialiasingMask;

/* When true this layer is allowed to antialias its edges, as requested
 * by the value of the edgeAntialiasingMask property.
 *
 * The default value is read from the boolean UIViewEdgeAntialiasing
 * property in the main bundle's Info.plist. If no value is found in
 * the Info.plist the default value is NO. */

@property BOOL allowsEdgeAntialiasing
    API_AVAILABLE(macos(10.10), ios(2.0), watchos(2.0), tvos(9.0));

/* The background color of the layer. Default value is nil. Colors
 * created from tiled patterns are supported. Animatable. */

@property(nullable) CGColorRef backgroundColor;

/* When positive, the background of the layer will be drawn with
 * rounded corners. Also effects the mask generated by the
 * `masksToBounds' property. Defaults to zero. Animatable. */

@property CGFloat cornerRadius;

/* Defines which of the four corners receives the masking when using
 * `cornerRadius' property. Defaults to all four corners. */

@property CACornerMask maskedCorners
  API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/* Defines the curve used for rendering the rounded corners of the layer.
 * Defaults to 'kCACornerCurveCircular'. */

@property(copy) CALayerCornerCurve cornerCurve
  API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/* Expansion scale factor applied to the rounded corner bounding box size
 * when specific corner curve is used. */

+ (CGFloat)cornerCurveExpansionFactor:(CALayerCornerCurve)curve
  API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/* The width of the layer's border, inset from the layer bounds. The
 * border is composited above the layer's content and sublayers and
 * includes the effects of the `cornerRadius' property. Defaults to
 * zero. Animatable. */

@property CGFloat borderWidth;

/* The color of the layer's border. Defaults to opaque black. Colors
 * created from tiled patterns are supported. Animatable. */

@property(nullable) CGColorRef borderColor;

/* The opacity of the layer, as a value between zero and one. Defaults
 * to one. Specifying a value outside the [0,1] range will give undefined
 * results. Animatable. */

@property float opacity;

/* When true, and the layer's opacity property is less than one, the
 * layer is allowed to composite itself as a group separate from its
 * parent. This gives the correct results when the layer contains
 * multiple opaque components, but may reduce performance.
 *
 * The default value of the property is read from the boolean
 * UIViewGroupOpacity property in the main bundle's Info.plist. If no
 * value is found in the Info.plist the default value is YES for
 * applications linked against the iOS 7 SDK or later and NO for
 * applications linked against an earlier SDK. */

@property BOOL allowsGroupOpacity
    API_AVAILABLE(macos(10.10), ios(2.0), watchos(2.0), tvos(9.0));

/* A filter object used to composite the layer with its (possibly
 * filtered) background. Default value is nil, which implies source-
 * over compositing. Animatable.
 *
 * Note that if the inputs of the filter are modified directly after
 * the filter is attached to a layer, the behavior is undefined. The
 * filter must either be reattached to the layer, or filter properties
 * should be modified by calling -setValue:forKeyPath: on each layer
 * that the filter is attached to. (This also applies to the `filters'
 * and `backgroundFilters' properties.) */

@property(nullable, strong) id compositingFilter;

/* An array of filters that will be applied to the contents of the
 * layer and its sublayers. Defaults to nil. Animatable. */

@property(nullable, copy) NSArray *filters;

/* An array of filters that are applied to the background of the layer.
 * The root layer ignores this property. Animatable. */

@property(nullable, copy) NSArray *backgroundFilters;

/* When true, the layer is rendered as a bitmap in its local coordinate
 * space ("rasterized"), then the bitmap is composited into the
 * destination (with the minificationFilter and magnificationFilter
 * properties of the layer applied if the bitmap needs scaling).
 * Rasterization occurs after the layer's filters and shadow effects
 * are applied, but before the opacity modulation. As an implementation
 * detail the rendering engine may attempt to cache and reuse the
 * bitmap from one frame to the next. (Whether it does or not will have
 * no affect on the rendered output.)
 *
 * When false the layer is composited directly into the destination
 * whenever possible (however, certain features of the compositing
 * model may force rasterization, e.g. adding filters).
 *
 * Defaults to NO. Animatable. */

@property BOOL shouldRasterize;

/* The scale at which the layer will be rasterized (when the
 * shouldRasterize property has been set to YES) relative to the
 * coordinate space of the layer. Defaults to one. Animatable. */

@property CGFloat rasterizationScale;

/** Shadow properties. **/

/* The color of the shadow. Defaults to opaque black. Colors created
 * from patterns are currently NOT supported. Animatable. */

@property(nullable) CGColorRef shadowColor;

/* The opacity of the shadow. Defaults to 0. Specifying a value outside the
 * [0,1] range will give undefined results. Animatable. */

@property float shadowOpacity;

/* The shadow offset. Defaults to (0, -3). Animatable. */

@property CGSize shadowOffset;

/* The blur radius used to create the shadow. Defaults to 3. Animatable. */

@property CGFloat shadowRadius;

/* When non-null this path defines the outline used to construct the
 * layer's shadow instead of using the layer's composited alpha
 * channel. The path is rendered using the non-zero winding rule.
 * Specifying the path explicitly using this property will usually
 * improve rendering performance, as will sharing the same path
 * reference across multiple layers. Upon assignment the path is copied.
 * Defaults to null. Animatable. */

@property(nullable) CGPathRef shadowPath;

/** Layout methods. **/

/* Returns the preferred frame size of the layer in the coordinate
 * space of the superlayer. The default implementation calls the layout
 * manager if one exists and it implements the -preferredSizeOfLayer:
 * method, otherwise returns the size of the bounds rect mapped into
 * the superlayer. */

- (CGSize)preferredFrameSize;

/* Marks that -layoutSublayers needs to be invoked on the receiver
 * before the next update. If the receiver's layout manager implements
 * the -invalidateLayoutOfLayer: method it will be called.
 *
 * This method is automatically invoked on a layer whenever its
 * `sublayers' or `layoutManager' property is modified, and is invoked
 * on the layer and its superlayer whenever its `bounds' or `transform'
 * properties are modified. Implicit calls to -setNeedsLayout are
 * skipped if the layer is currently executing its -layoutSublayers
 * method. */

- (void)setNeedsLayout;

/* Returns true when the receiver is marked as needing layout. */

- (BOOL)needsLayout;

/* Traverse upwards from the layer while the superlayer requires layout.
 * Then layout the entire tree beneath that ancestor. */

- (void)layoutIfNeeded;

/* Called when the layer requires layout. The default implementation
 * calls the layout manager if one exists and it implements the
 * -layoutSublayersOfLayer: method. Subclasses can override this to
 * provide their own layout algorithm, which should set the frame of
 * each sublayer. */

- (void)layoutSublayers;

/** Action methods. **/

/* An "action" is an object that responds to an "event" via the
 * CAAction protocol (see below). Events are named using standard
 * dot-separated key paths. Each layer defines a mapping from event key
 * paths to action objects. Events are posted by looking up the action
 * object associated with the key path and sending it the method
 * defined by the CAAction protocol.
 *
 * When an action object is invoked it receives three parameters: the
 * key path naming the event, the object on which the event happened
 * (i.e. the layer), and optionally a dictionary of named arguments
 * specific to each event.
 *
 * To provide implicit animations for layer properties, an event with
 * the same name as each property is posted whenever the value of the
 * property is modified. A suitable CAAnimation object is associated by
 * default with each implicit event (CAAnimation implements the action
 * protocol).
 *
 * The layer class also defines the following events that are not
 * linked directly to properties:
 *
 * onOrderIn
 *      Invoked when the layer is made visible, i.e. either its
 *      superlayer becomes visible, or it's added as a sublayer of a
 *      visible layer
 *
 * onOrderOut
 *      Invoked when the layer becomes non-visible. */

/* Returns the default action object associated with the event named by
 * the string 'event'. The default implementation returns a suitable
 * animation object for events posted by animatable properties, nil
 * otherwise. */

+ (nullable id<CAAction>)defaultActionForKey:(NSString *)event;

/* Returns the action object associated with the event named by the
 * string 'event'. The default implementation searches for an action
 * object in the following places:
 *
 * 1. if defined, call the delegate method -actionForLayer:forKey:
 * 2. look in the layer's `actions' dictionary
 * 3. look in any `actions' dictionaries in the `style' hierarchy
 * 4. call +defaultActionForKey: on the layer's class
 *
 * If any of these steps results in a non-nil action object, the
 * following steps are ignored. If the final result is an instance of
 * NSNull, it is converted to `nil'. */

- (nullable id<CAAction>)actionForKey:(NSString *)event;

/* A dictionary mapping keys to objects implementing the CAAction
 * protocol. Default value is nil. */

@property(nullable, copy) NSDictionary<NSString *, id<CAAction>> *actions;

/** Animation methods. **/

/* Attach an animation object to the layer. Typically this is implicitly
 * invoked through an action that is an CAAnimation object.
 *
 * 'key' may be any string such that only one animation per unique key
 * is added per layer. The special key 'transition' is automatically
 * used for transition animations. The nil pointer is also a valid key.
 *
 * If the `duration' property of the animation is zero or negative it
 * is given the default duration, either the value of the
 * `animationDuration' transaction property or .25 seconds otherwise.
 *
 * The animation is copied before being added to the layer, so any
 * subsequent modifications to `anim' will have no affect unless it is
 * added to another layer. */

- (void)addAnimation:(CAAnimation *)anim forKey:(nullable NSString *)key;

/* Remove all animations attached to the layer. */

- (void)removeAllAnimations;

/* Remove any animation attached to the layer for 'key'. */

- (void)removeAnimationForKey:(NSString *)key;

/* Returns an array containing the keys of all animations currently
 * attached to the receiver. The order of the array matches the order
 * in which animations will be applied. */

- (nullable NSArray<NSString *> *)animationKeys;

/* Returns the animation added to the layer with identifier 'key', or nil
 * if no such animation exists. Attempting to modify any properties of
 * the returned object will result in undefined behavior. */

- (nullable __kindof CAAnimation *)animationForKey:(NSString *)key;


/** Miscellaneous properties. **/

/* The name of the layer. Used by some layout managers. Defaults to nil. */

@property(nullable, copy) NSString *name;

/* An object that will receive the CALayer delegate methods defined
 * below (for those that it implements). The value of this property is
 * not retained. Default value is nil. */

@property(nullable, weak) id <CALayerDelegate> delegate;

/* When non-nil, a dictionary dereferenced to find property values that
 * aren't explicitly defined by the layer. (This dictionary may in turn
 * have a `style' property, forming a hierarchy of default values.)
 * If the style dictionary doesn't define a value for an attribute, the
 * +defaultValueForKey: method is called. Defaults to nil.
 *
 * Note that if the dictionary or any of its ancestors are modified,
 * the values of the layer's properties are undefined until the `style'
 * property is reset. */

@property(nullable, copy) NSDictionary *style;

@end

/** Action (event handler) protocol. **/

@protocol CAAction

/* Called to trigger the event named 'path' on the receiver. The object
 * (e.g. the layer) on which the event happened is 'anObject'. The
 * arguments dictionary may be nil, if non-nil it carries parameters
 * associated with the event. */

- (void)runActionForKey:(NSString *)event object:(id)anObject
    arguments:(nullable NSDictionary *)dict;

@end

/** NSNull protocol conformance. **/

@interface NSNull (CAActionAdditions) <CAAction>

@end

/** Delegate methods. **/

@protocol CALayerDelegate <NSObject>
@optional

/* If defined, called by the default implementation of the -display
 * method, in which case it should implement the entire display
 * process (typically by setting the `contents' property). */

- (void)displayLayer:(CALayer *)layer;

/* If defined, called by the default implementation of -drawInContext: */

- (void)drawLayer:(CALayer *)layer inContext:(CGContextRef)ctx;

/* If defined, called by the default implementation of the -display method.
 * Allows the delegate to configure any layer state affecting contents prior
 * to -drawLayer:InContext: such as `contentsFormat' and `opaque'. It will not
 * be called if the delegate implements -displayLayer. */

- (void)layerWillDraw:(CALayer *)layer
  API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/* Called by the default -layoutSublayers implementation before the layout
 * manager is checked. Note that if the delegate method is invoked, the
 * layout manager will be ignored. */

- (void)layoutSublayersOfLayer:(CALayer *)layer;

/* If defined, called by the default implementation of the
 * -actionForKey: method. Should return an object implementing the
 * CAAction protocol. May return 'nil' if the delegate doesn't specify
 * a behavior for the current event. Returning the null object (i.e.
 * '[NSNull null]') explicitly forces no further search. (I.e. the
 * +defaultActionForKey: method will not be called.) */

- (nullable id<CAAction>)actionForLayer:(CALayer *)layer forKey:(NSString *)event;

@end

/** Layer `contentsGravity' values. **/

CA_EXTERN CALayerContentsGravity const kCAGravityCenter
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CALayerContentsGravity const kCAGravityTop
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CALayerContentsGravity const kCAGravityBottom
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CALayerContentsGravity const kCAGravityLeft
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CALayerContentsGravity const kCAGravityRight
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CALayerContentsGravity const kCAGravityTopLeft
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CALayerContentsGravity const kCAGravityTopRight
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CALayerContentsGravity const kCAGravityBottomLeft
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CALayerContentsGravity const kCAGravityBottomRight
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CALayerContentsGravity const kCAGravityResize
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CALayerContentsGravity const kCAGravityResizeAspect
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CALayerContentsGravity const kCAGravityResizeAspectFill
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/** Layer `contentsFormat` values. **/

CA_EXTERN CALayerContentsFormat const kCAContentsFormatRGBA8Uint /* RGBA UInt8 per component */
  API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));
CA_EXTERN CALayerContentsFormat const kCAContentsFormatRGBA16Float /* RGBA half-float 16-bit per component */
  API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));
CA_EXTERN CALayerContentsFormat const kCAContentsFormatGray8Uint /* Grayscale with alpha (if not opaque) UInt8 per component */
  API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/** Contents filter names. **/

CA_EXTERN CALayerContentsFilter const kCAFilterNearest
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CALayerContentsFilter const kCAFilterLinear
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Trilinear minification filter. Enables mipmap generation. Some
 * renderers may ignore this, or impose additional restrictions, such
 * as source images requiring power-of-two dimensions. */

CA_EXTERN CALayerContentsFilter const kCAFilterTrilinear
    API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));

/** Corner curve names. **/

CA_EXTERN CALayerCornerCurve const kCACornerCurveCircular
    API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));
CA_EXTERN CALayerCornerCurve const kCACornerCurveContinuous
    API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/** Layer event names. **/

CA_EXTERN NSString * const kCAOnOrderIn
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN NSString * const kCAOnOrderOut
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/** The animation key used for transitions. **/

CA_EXTERN NSString * const kCATransition
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

NS_ASSUME_NONNULL_END
// ==========  QuartzCore.framework/Headers/CAMediaTimingFunction.h
/* CoreAnimation - CAMediaTimingFunction.h

   Copyright (c) 2006-2018, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CAMediaTiming.h>
#import <Foundation/NSObject.h>

@class NSArray, NSString;

NS_ASSUME_NONNULL_BEGIN

typedef NSString * CAMediaTimingFunctionName NS_TYPED_ENUM;

/* Represents one segment of a function describing a timing curve. The
 * function maps an input time normalized to the range [0,1] to an
 * output time also in the range [0,1]. E.g. these functions are used
 * to define the pacing of an animation over its duration (or over the
 * duration of one keyframe). */

API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
@interface CAMediaTimingFunction : NSObject <NSSecureCoding>
{
@private
  struct CAMediaTimingFunctionPrivate *_priv;
}

/* A convenience method for creating common timing functions. The
 * currently supported names are `linear', `easeIn', `easeOut' and
 * `easeInEaseOut' and `default' (the curve used by implicit animations
 * created by Core Animation). */

+ (instancetype)functionWithName:(CAMediaTimingFunctionName)name;

/* Creates a timing function modelled on a cubic Bezier curve. The end
 * points of the curve are at (0,0) and (1,1), the two points 'c1' and
 * 'c2' defined by the class instance are the control points. Thus the
 * points defining the Bezier curve are: '[(0,0), c1, c2, (1,1)]' */

+ (instancetype)functionWithControlPoints:(float)c1x :(float)c1y :(float)c2x :(float)c2y;

- (instancetype)initWithControlPoints:(float)c1x :(float)c1y :(float)c2x :(float)c2y;

/* 'idx' is a value from 0 to 3 inclusive. */

- (void)getControlPointAtIndex:(size_t)idx values:(float[_Nonnull 2])ptr;

@end

/** Timing function names. **/

CA_EXTERN CAMediaTimingFunctionName const kCAMediaTimingFunctionLinear
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAMediaTimingFunctionName const kCAMediaTimingFunctionEaseIn
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAMediaTimingFunctionName const kCAMediaTimingFunctionEaseOut
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAMediaTimingFunctionName const kCAMediaTimingFunctionEaseInEaseOut
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAMediaTimingFunctionName const kCAMediaTimingFunctionDefault
    API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));

NS_ASSUME_NONNULL_END
// ==========  QuartzCore.framework/Headers/CAReplicatorLayer.h
/* CoreAnimation - CAReplicatorLayer.h

   Copyright (c) 2008-2018, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CALayer.h>

NS_ASSUME_NONNULL_BEGIN

/* The replicator layer creates a specified number of copies of its
 * sublayers, each copy potentially having geometric, temporal and
 * color transformations applied to it.
 *
 * Note: the CALayer -hitTest: method currently only tests the first
 * instance of z replicator layer's sublayers. This may change in the
 * future. */

API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0))
@interface CAReplicatorLayer : CALayer

/* The number of copies to create, including the source object.
 * Default value is one (i.e. no extra copies). Animatable. */

@property NSInteger instanceCount;

/* Defines whether this layer flattens its sublayers into its plane or
 * not (i.e. whether it's treated similarly to a transform layer or
 * not). Defaults to NO. If YES, the standard restrictions apply (see
 * CATransformLayer.h). */

@property BOOL preservesDepth;

/* The temporal delay between replicated copies. Defaults to zero.
 * Animatable. */

@property CFTimeInterval instanceDelay;

/* The matrix applied to instance k-1 to produce instance k. The matrix
 * is applied relative to the center of the replicator layer, i.e. the
 * superlayer of each replicated sublayer. Defaults to the identity
 * matrix. Animatable. */

@property CATransform3D instanceTransform;

/* The color to multiply the first object by (the source object). Defaults
 * to opaque white. Animatable. */

@property(nullable) CGColorRef instanceColor;

/* The color components added to the color of instance k-1 to produce
 * the modulation color of instance k. Defaults to the clear color (no
 * change). Animatable. */

@property float instanceRedOffset;
@property float instanceGreenOffset;
@property float instanceBlueOffset;
@property float instanceAlphaOffset;

@end

NS_ASSUME_NONNULL_END
// ==========  QuartzCore.framework/Headers/CATextLayer.h
/* CoreAnimation - CATextLayer.h

   Copyright (c) 2006-2018, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CALayer.h>

/* The text layer provides simple text layout and rendering of plain
 * or attributed strings. The first line is aligned to the top of the
 * layer. */

NS_ASSUME_NONNULL_BEGIN

typedef NSString * CATextLayerTruncationMode NS_TYPED_ENUM;
typedef NSString * CATextLayerAlignmentMode NS_TYPED_ENUM;

API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
@interface CATextLayer : CALayer
{
@private
  struct CATextLayerPrivate *_state;
}

/* The text to be rendered, should be either an NSString or an
 * NSAttributedString. Defaults to nil. */

@property(nullable, copy) id string;

/* The font to use, currently may be either a CTFontRef (toll-free
 * bridged from UIFont), a CGFontRef, or a string naming the font.
 * Defaults to the Helvetica font. Only used when the `string' property
 * is not an NSAttributedString. */

@property(nullable) CFTypeRef font;

/* The font size. Defaults to 36. Only used when the `string' property
 * is not an NSAttributedString. Animatable (Mac OS X 10.6 and later.) */

@property CGFloat fontSize;

/* The color object used to draw the text. Defaults to opaque white.
 * Only used when the `string' property is not an NSAttributedString.
 * Animatable (Mac OS X 10.6 and later.) */

@property(nullable) CGColorRef foregroundColor;

/* When true the string is wrapped to fit within the layer bounds.
 * Defaults to NO.*/

@property(getter=isWrapped) BOOL wrapped;

/* Describes how the string is truncated to fit within the layer
 * bounds. The possible options are `none', `start', `middle' and
 * `end'. Defaults to `none'. */

@property(copy) CATextLayerTruncationMode truncationMode;

/* Describes how individual lines of text are aligned within the layer
 * bounds. The possible options are `natural', `left', `right',
 * `center' and `justified'. Defaults to `natural'. */

@property(copy) CATextLayerAlignmentMode alignmentMode;

/* Sets allowsFontSubpixelQuantization parameter of CGContextRef
 * passed to the -drawInContext: method. Defaults to NO. */

@property BOOL allowsFontSubpixelQuantization;

@end

/* Truncation modes. */

CA_EXTERN CATextLayerTruncationMode const kCATruncationNone
    API_AVAILABLE(macos(10.5), ios(3.2), watchos(2.0), tvos(9.0));
CA_EXTERN CATextLayerTruncationMode const kCATruncationStart
    API_AVAILABLE(macos(10.5), ios(3.2), watchos(2.0), tvos(9.0));
CA_EXTERN CATextLayerTruncationMode const kCATruncationEnd
    API_AVAILABLE(macos(10.5), ios(3.2), watchos(2.0), tvos(9.0));
CA_EXTERN CATextLayerTruncationMode const kCATruncationMiddle
    API_AVAILABLE(macos(10.5), ios(3.2), watchos(2.0), tvos(9.0));

/* Alignment modes. */

CA_EXTERN CATextLayerAlignmentMode const kCAAlignmentNatural
    API_AVAILABLE(macos(10.5), ios(3.2), watchos(2.0), tvos(9.0));
CA_EXTERN CATextLayerAlignmentMode const kCAAlignmentLeft
    API_AVAILABLE(macos(10.5), ios(3.2), watchos(2.0), tvos(9.0));
CA_EXTERN CATextLayerAlignmentMode const kCAAlignmentRight
    API_AVAILABLE(macos(10.5), ios(3.2), watchos(2.0), tvos(9.0));
CA_EXTERN CATextLayerAlignmentMode const kCAAlignmentCenter
    API_AVAILABLE(macos(10.5), ios(3.2), watchos(2.0), tvos(9.0));
CA_EXTERN CATextLayerAlignmentMode const kCAAlignmentJustified
    API_AVAILABLE(macos(10.5), ios(3.2), watchos(2.0), tvos(9.0));

NS_ASSUME_NONNULL_END
// ==========  QuartzCore.framework/Headers/CATiledLayer.h
/* CoreAnimation - CATiledLayer.h

   Copyright (c) 2006-2018, Apple Inc.
   All rights reserved. */

/* This is a subclass of CALayer providing a way to asynchronously
 * provide tiles of the layer's content, potentially cached at multiple
 * levels of detail.
 *
 * As more data is required by the renderer, the layer's
 * -drawInContext: method is called on one or more background threads
 * to supply the drawing operations to fill in one tile of data. The
 * clip bounds and CTM of the drawing context can be used to determine
 * the bounds and resolution of the tile being requested.
 *
 * Regions of the layer may be invalidated using the usual
 * -setNeedsDisplayInRect: method. However update will be asynchronous,
 * i.e. the next display update will most likely not contain the
 * changes, but a future update will.
 *
 * Note: do not attempt to directly modify the `contents' property of
 * an CATiledLayer object - doing so will effectively turn it into a
 * regular CALayer. */

#import <QuartzCore/CALayer.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
@interface CATiledLayer : CALayer

/* The time in seconds that newly added images take to "fade-in" to the
 * rendered representation of the tiled layer. The default implementation
 * returns 0.25 seconds. */

+ (CFTimeInterval)fadeDuration;

/* The number of levels of detail maintained by this layer. Defaults to
 * one. Each LOD is half the resolution of the previous level. If too
 * many levels are specified for the current size of the layer, then
 * the number of levels is clamped to the maximum value (the bottom
 * most LOD must contain at least a single pixel in each dimension). */

@property size_t levelsOfDetail;

/* The number of magnified levels of detail for this layer. Defaults to
 * zero. Each previous level of detail is twice the resolution of the
 * later. E.g. specifying 'levelsOfDetailBias' of two means that the
 * layer devotes two of its specified levels of detail to
 * magnification, i.e. 2x and 4x. */

@property size_t levelsOfDetailBias;

/* The maximum size of each tile used to create the layer's content.
 * Defaults to (256, 256). Note that there is a maximum tile size, and
 * requests for tiles larger than that limit will cause a suitable
 * value to be substituted. */

@property CGSize tileSize;

@end

NS_ASSUME_NONNULL_END
// ==========  QuartzCore.framework/Headers/CAEmitterLayer.h
/* CoreAnimation - CAEmitterLayer.h

   Copyright (c) 2007-2018, Apple Inc.
   All rights reserved. */

/* Particle emitter layer.
 *
 * Each emitter has an array of cells, the cells define how particles
 * are emitted and rendered by the layer.
 *
 * Particle system is affected by layer's timing. The simulation starts
 * at layer's beginTime.
 *
 * The particles are drawn above the backgroundColor and border of the
 * layer. */

#import <QuartzCore/CALayer.h>

typedef NSString * CAEmitterLayerEmitterShape NS_TYPED_ENUM;
typedef NSString * CAEmitterLayerEmitterMode NS_TYPED_ENUM;
typedef NSString * CAEmitterLayerRenderMode NS_TYPED_ENUM;

@class CAEmitterCell;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.6), ios(5.0), watchos(2.0), tvos(9.0))
@interface CAEmitterLayer : CALayer

/* The array of emitter cells attached to the layer. Each object must
 * have the CAEmitterCell class. */

@property(nullable, copy) NSArray<CAEmitterCell *> *emitterCells;

/* The birth rate of each cell is multiplied by this number to give the
 * actual number of particles created every second. Default value is one.
 * Animatable. */

@property float birthRate;

/* The cell lifetime range is multiplied by this value when particles are
 * created. Defaults to one. Animatable. */

@property float lifetime;

/* The center of the emission shape. Defaults to (0, 0, 0). Animatable. */

@property CGPoint emitterPosition;
@property CGFloat emitterZPosition;

/* The size of the emission shape. Defaults to (0, 0, 0). Animatable.
 * Depending on the `emitterShape' property some of the values may be
 * ignored. */

@property CGSize emitterSize;
@property CGFloat emitterDepth;

/* A string defining the type of emission shape used. Current options are:
 * `point' (the default), `line', `rectangle', `circle', `cuboid' and
 * `sphere'. */

@property(copy) CAEmitterLayerEmitterShape emitterShape;

/* A string defining how particles are created relative to the emission
 * shape. Current options are `points', `outline', `surface' and
 * `volume' (the default). */

@property(copy) CAEmitterLayerEmitterMode emitterMode;

/* A string defining how particles are composited into the layer's
 * image. Current options are `unordered' (the default), `oldestFirst',
 * `oldestLast', `backToFront' (i.e. sorted into Z order) and
 * `additive'. The first four use source-over compositing, the last
 * uses additive compositing. */

@property(copy) CAEmitterLayerRenderMode renderMode;

/* When true the particles are rendered as if they directly inhabit the
 * three dimensional coordinate space of the layer's superlayer, rather
 * than being flattened into the layer's plane first. Defaults to NO.
 * If true, the effect of the `filters', `backgroundFilters' and shadow-
 * related properties of the layer is undefined. */

@property BOOL preservesDepth;

/* Multiplies the cell-defined particle velocity. Defaults to one.
 * Animatable. */

@property float velocity;

/* Multiplies the cell-defined particle scale. Defaults to one. Animatable. */

@property float scale;

/* Multiplies the cell-defined particle spin. Defaults to one. Animatable. */

@property float spin;

/* The seed used to initialize the random number generator. Defaults to
 * zero. Each layer has its own RNG state. For properties with a mean M
 * and a range R, random values of the properties are uniformly
 * distributed in the interval [M - R/2, M + R/2]. */

@property unsigned int seed;

@end

/** `emitterShape' values. **/

CA_EXTERN CAEmitterLayerEmitterShape const kCAEmitterLayerPoint
    API_AVAILABLE(macos(10.6), ios(5.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAEmitterLayerEmitterShape const kCAEmitterLayerLine
    API_AVAILABLE(macos(10.6), ios(5.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAEmitterLayerEmitterShape const kCAEmitterLayerRectangle
    API_AVAILABLE(macos(10.6), ios(5.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAEmitterLayerEmitterShape const kCAEmitterLayerCuboid
    API_AVAILABLE(macos(10.6), ios(5.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAEmitterLayerEmitterShape const kCAEmitterLayerCircle
    API_AVAILABLE(macos(10.6), ios(5.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAEmitterLayerEmitterShape const kCAEmitterLayerSphere
    API_AVAILABLE(macos(10.6), ios(5.0), watchos(2.0), tvos(9.0));

/** `emitterMode' values. **/

CA_EXTERN CAEmitterLayerEmitterMode const kCAEmitterLayerPoints
    API_AVAILABLE(macos(10.6), ios(5.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAEmitterLayerEmitterMode const kCAEmitterLayerOutline
    API_AVAILABLE(macos(10.6), ios(5.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAEmitterLayerEmitterMode const kCAEmitterLayerSurface
    API_AVAILABLE(macos(10.6), ios(5.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAEmitterLayerEmitterMode const kCAEmitterLayerVolume
    API_AVAILABLE(macos(10.6), ios(5.0), watchos(2.0), tvos(9.0));

/** `renderMode' values. **/

CA_EXTERN CAEmitterLayerRenderMode const kCAEmitterLayerUnordered
    API_AVAILABLE(macos(10.6), ios(5.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAEmitterLayerRenderMode const kCAEmitterLayerOldestFirst
    API_AVAILABLE(macos(10.6), ios(5.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAEmitterLayerRenderMode const kCAEmitterLayerOldestLast
    API_AVAILABLE(macos(10.6), ios(5.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAEmitterLayerRenderMode const kCAEmitterLayerBackToFront
    API_AVAILABLE(macos(10.6), ios(5.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAEmitterLayerRenderMode const kCAEmitterLayerAdditive
    API_AVAILABLE(macos(10.6), ios(5.0), watchos(2.0), tvos(9.0));

NS_ASSUME_NONNULL_END
// ==========  QuartzCore.framework/Headers/CADisplayLink.h
/* CoreAnimation - CADisplayLink.h

   Copyright (c) 2009-2018, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CABase.h>
#import <Foundation/NSObject.h>

@class NSString, NSRunLoop;

NS_ASSUME_NONNULL_BEGIN

/** Class representing a timer bound to the display vsync. **/

API_AVAILABLE(ios(3.1), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos)
@interface CADisplayLink : NSObject
{
@private
  void *_impl;
}

/* Create a new display link object for the main display. It will
 * invoke the method called 'sel' on 'target', the method has the
 * signature '(void)selector:(CADisplayLink *)sender'. */

+ (CADisplayLink *)displayLinkWithTarget:(id)target selector:(SEL)sel;

/* Adds the receiver to the given run-loop and mode. Unless paused, it
 * will fire every vsync until removed. Each object may only be added
 * to a single run-loop, but it may be added in multiple modes at once.
 * While added to a run-loop it will implicitly be retained. */

- (void)addToRunLoop:(NSRunLoop *)runloop forMode:(NSRunLoopMode)mode;

/* Removes the receiver from the given mode of the runloop. This will
 * implicitly release it when removed from the last mode it has been
 * registered for. */

- (void)removeFromRunLoop:(NSRunLoop *)runloop forMode:(NSRunLoopMode)mode;

/* Removes the object from all runloop modes (releasing the receiver if
 * it has been implicitly retained) and releases the 'target' object. */

- (void)invalidate;

/* The current time, and duration of the display frame associated with
 * the most recent target invocation. Time is represented using the
 * normal Core Animation conventions, i.e. Mach host time converted to
 * seconds. */

@property(readonly, nonatomic) CFTimeInterval timestamp;
@property(readonly, nonatomic) CFTimeInterval duration;

/* The next timestamp that the client should target their render for. */

@property(readonly, nonatomic) CFTimeInterval targetTimestamp
    API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0));

/* When true the object is prevented from firing. Initial state is
 * false. */

@property(getter=isPaused, nonatomic) BOOL paused;

/* Defines how many display frames must pass between each time the
 * display link fires. Default value is one, which means the display
 * link will fire for every display frame. Setting the interval to two
 * will cause the display link to fire every other display frame, and
 * so on. The behavior when using values less than one is undefined.
 * DEPRECATED - use preferredFramesPerSecond. */

@property(nonatomic) NSInteger frameInterval
  API_DEPRECATED("preferredFramesPerSecond", ios(3.1, 10.0), 
                 watchos(2.0, 3.0), tvos(9.0, 10.0));

/* Defines the desired callback rate in frames-per-second for this display
 * link. If set to zero, the default value, the display link will fire at the
 * native cadence of the display hardware. The display link will make a
 * best-effort attempt at issuing callbacks at the requested rate. */

@property(nonatomic) NSInteger preferredFramesPerSecond
    API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0));

@end

NS_ASSUME_NONNULL_END
// ==========  QuartzCore.framework/Headers/CAMediaTiming.h
/* CoreAnimation - CAMediaTiming.h

   Copyright (c) 2006-2018, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CABase.h>
#import <objc/objc.h>
#import <Foundation/NSObject.h>

/* The CAMediaTiming protocol is implemented by layers and animations, it
 * models a hierarchical timing system, with each object describing the
 * mapping from time values in the object's parent to local time.
 *
 * Absolute time is defined as mach time converted to seconds. The
 * CACurrentMediaTime function is provided as a convenience for querying the
 * current absolute time.
 *
 * The conversion from parent time to local time has two stages:
 *
 * 1. conversion to "active local time". This includes the point at
 * which the object appears in the parent's timeline, and how fast it
 * plays relative to the parent.
 *
 * 2. conversion from active to "basic local time". The timing model
 * allows for objects to repeat their basic duration multiple times,
 * and optionally to play backwards before repeating. */

@class NSString;

typedef NSString * CAMediaTimingFillMode NS_TYPED_ENUM;

NS_ASSUME_NONNULL_BEGIN

@protocol CAMediaTiming

/* The begin time of the object, in relation to its parent object, if
 * applicable. Defaults to 0. */

@property CFTimeInterval beginTime;

/* The basic duration of the object. Defaults to 0. */

@property CFTimeInterval duration;

/* The rate of the layer. Used to scale parent time to local time, e.g.
 * if rate is 2, local time progresses twice as fast as parent time.
 * Defaults to 1. */

@property float speed;

/* Additional offset in active local time. i.e. to convert from parent
 * time tp to active local time t: t = (tp - begin) * speed + offset.
 * One use of this is to "pause" a layer by setting `speed' to zero and
 * `offset' to a suitable value. Defaults to 0. */

@property CFTimeInterval timeOffset;

/* The repeat count of the object. May be fractional. Defaults to 0. */

@property float repeatCount;

/* The repeat duration of the object. Defaults to 0. */

@property CFTimeInterval repeatDuration;

/* When true, the object plays backwards after playing forwards. Defaults
 * to NO. */

@property BOOL autoreverses;

/* Defines how the timed object behaves outside its active duration.
 * Local time may be clamped to either end of the active duration, or
 * the element may be removed from the presentation. The legal values
 * are `backwards', `forwards', `both' and `removed'. Defaults to
 * `removed'. */

@property(copy) CAMediaTimingFillMode fillMode;

@end

/* `fillMode' options. */

CA_EXTERN CAMediaTimingFillMode const kCAFillModeForwards
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAMediaTimingFillMode const kCAFillModeBackwards
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAMediaTimingFillMode const kCAFillModeBoth
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAMediaTimingFillMode const kCAFillModeRemoved
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

NS_ASSUME_NONNULL_END
// ==========  QuartzCore.framework/Headers/CAEAGLLayer.h
/* CoreAnimation - CAEAGLLayer.h

   Copyright (c) 2007-2018, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CALayer.h>
#import <OpenGLES/EAGLDrawable.h>

NS_ASSUME_NONNULL_BEGIN

/* CAEAGLLayer is a layer that implements the EAGLDrawable protocol,
 * allowing it to be used as an OpenGLES render target. Use the
 * `drawableProperties' property defined by the protocol to configure
 * the created surface. */

#ifndef GLES_SILENCE_DEPRECATION
API_DEPRECATED("OpenGLES is deprecated",
               ios(2.0, 12.0), watchos(2.0, 5.0), tvos(9.0, 12.0))
#else
API_AVAILABLE(ios(2.0), watchos(2.0), tvos(9.0))
#endif
API_UNAVAILABLE(macos)
@interface CAEAGLLayer : CALayer <EAGLDrawable>
{
@private
  struct _CAEAGLNativeWindow *_win;
}

/* When false (the default value) changes to the layer's render buffer
 * appear on-screen asynchronously to normal layer updates. When true,
 * changes to the GLES content are sent to the screen via the standard
 * CATransaction mechanisms. */

@property BOOL presentsWithTransaction API_AVAILABLE(ios(9.0), watchos(2.0), tvos(9.0));

/* Note: the default value of the `opaque' property in this class is true,
 * not false as in CALayer. */

@end

NS_ASSUME_NONNULL_END
// ==========  QuartzCore.framework/Headers/CoreAnimation.h
/* CoreAnimation - CoreAnimation.h

   Copyright (c) 2006-2018, Apple Inc.
   All rights reserved. */

#ifndef COREANIMATION_H
#define COREANIMATION_H

#include <QuartzCore/CABase.h>
#include <QuartzCore/CATransform3D.h>

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#import <QuartzCore/CAAnimation.h>
#import <QuartzCore/CADisplayLink.h>
#import <QuartzCore/CAEAGLLayer.h>
#import <QuartzCore/CAMetalLayer.h>
#import <QuartzCore/CAEmitterCell.h>
#import <QuartzCore/CAEmitterLayer.h>
#import <QuartzCore/CAGradientLayer.h>
#import <QuartzCore/CALayer.h>
#import <QuartzCore/CAMediaTiming.h>
#import <QuartzCore/CAMediaTimingFunction.h>
#import <QuartzCore/CAReplicatorLayer.h>
#import <QuartzCore/CAScrollLayer.h>
#import <QuartzCore/CAShapeLayer.h>
#import <QuartzCore/CATextLayer.h>
#import <QuartzCore/CATiledLayer.h>
#import <QuartzCore/CATransaction.h>
#import <QuartzCore/CATransform3D.h>
#import <QuartzCore/CATransformLayer.h>
#import <QuartzCore/CAValueFunction.h>
#endif

#endif /* COREANIMATION_H */
// ==========  QuartzCore.framework/Headers/CATransform3D.h
/* CoreAnimation - CATransform3D.h

   Copyright (c) 2006-2018, Apple Inc.
   All rights reserved. */

#ifndef CATRANSFORM_H
#define CATRANSFORM_H

#include <QuartzCore/CABase.h>

#ifdef __OBJC__
#import <Foundation/NSValue.h>
#endif

/* Homogeneous three-dimensional transforms. */

struct CATransform3D
{
  CGFloat m11, m12, m13, m14;
  CGFloat m21, m22, m23, m24;
  CGFloat m31, m32, m33, m34;
  CGFloat m41, m42, m43, m44;
};

typedef struct CA_BOXABLE CATransform3D CATransform3D;

CA_EXTERN_C_BEGIN

/* The identity transform: [1 0 0 0; 0 1 0 0; 0 0 1 0; 0 0 0 1]. */

CA_EXTERN const CATransform3D CATransform3DIdentity
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Returns true if 't' is the identity transform. */

CA_EXTERN bool CATransform3DIsIdentity (CATransform3D t)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Returns true if 'a' is exactly equal to 'b'. */

CA_EXTERN bool CATransform3DEqualToTransform (CATransform3D a,
    CATransform3D b)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Returns a transform that translates by '(tx, ty, tz)':
 * t' =  [1 0 0 0; 0 1 0 0; 0 0 1 0; tx ty tz 1]. */

CA_EXTERN CATransform3D CATransform3DMakeTranslation (CGFloat tx,
    CGFloat ty, CGFloat tz)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Returns a transform that scales by `(sx, sy, sz)':
 * t' = [sx 0 0 0; 0 sy 0 0; 0 0 sz 0; 0 0 0 1]. */

CA_EXTERN CATransform3D CATransform3DMakeScale (CGFloat sx, CGFloat sy,
    CGFloat sz)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Returns a transform that rotates by 'angle' radians about the vector
 * '(x, y, z)'. If the vector has length zero the identity transform is
 * returned. */

CA_EXTERN CATransform3D CATransform3DMakeRotation (CGFloat angle, CGFloat x,
    CGFloat y, CGFloat z)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Translate 't' by '(tx, ty, tz)' and return the result:
 * t' = translate(tx, ty, tz) * t. */

CA_EXTERN CATransform3D CATransform3DTranslate (CATransform3D t, CGFloat tx,
    CGFloat ty, CGFloat tz)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Scale 't' by '(sx, sy, sz)' and return the result:
 * t' = scale(sx, sy, sz) * t. */

CA_EXTERN CATransform3D CATransform3DScale (CATransform3D t, CGFloat sx,
    CGFloat sy, CGFloat sz)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Rotate 't' by 'angle' radians about the vector '(x, y, z)' and return
 * the result. If the vector has zero length the behavior is undefined:
 * t' = rotation(angle, x, y, z) * t. */

CA_EXTERN CATransform3D CATransform3DRotate (CATransform3D t, CGFloat angle,
    CGFloat x, CGFloat y, CGFloat z)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Concatenate 'b' to 'a' and return the result: t' = a * b. */

CA_EXTERN CATransform3D CATransform3DConcat (CATransform3D a, CATransform3D b)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Invert 't' and return the result. Returns the original matrix if 't'
 * has no inverse. */

CA_EXTERN CATransform3D CATransform3DInvert (CATransform3D t)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Return a transform with the same effect as affine transform 'm'. */

CA_EXTERN CATransform3D CATransform3DMakeAffineTransform (CGAffineTransform m)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Returns true if 't' can be represented exactly by an affine transform. */

CA_EXTERN bool CATransform3DIsAffine (CATransform3D t)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Returns the affine transform represented by 't'. If 't' can not be
 * represented exactly by an affine transform the returned value is
 * undefined. */

CA_EXTERN CGAffineTransform CATransform3DGetAffineTransform (CATransform3D t)
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

CA_EXTERN_C_END

/** NSValue support. **/

#ifdef __OBJC__

NS_ASSUME_NONNULL_BEGIN

@interface NSValue (CATransform3DAdditions)

+ (NSValue *)valueWithCATransform3D:(CATransform3D)t;

@property(readonly) CATransform3D CATransform3DValue;

@end

NS_ASSUME_NONNULL_END

#endif /* __OBJC__ */

#endif /* CATRANSFORM_H */
// ==========  QuartzCore.framework/Headers/CAEmitterCell.h
/* CoreAnimation - CAEmitterCell.h

   Copyright (c) 2007-2018, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CALayer.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.6), ios(5.0), watchos(2.0), tvos(9.0))
@interface CAEmitterCell : NSObject <NSSecureCoding, CAMediaTiming>
{
@private
  void *_attr[2];
  void *_state;
  uint32_t _flags;
}

+ (instancetype)emitterCell;

/* Emitter cells implement the same property model as defined by CALayer.
 * See CALayer.h for more details. */

+ (nullable id)defaultValueForKey:(NSString *)key;
- (BOOL)shouldArchiveValueForKey:(NSString *)key;

/* The name of the cell. Used to construct key paths. Defaults to nil. */

@property(nullable, copy) NSString *name;

/* Controls whether or not cells from this emitter are rendered. */

@property(getter=isEnabled) BOOL enabled;

/* The number of emitted objects created every second. Default value is
 * zero. Animatable. */

@property float birthRate;

/* The lifetime of each emitted object in seconds, specified as a mean
 * value and a range about the mean. Both values default to zero.
 * Animatable. */

@property float lifetime;
@property float lifetimeRange;

/* The orientation of the emission angle in radians, relative to the
 * natural orientation angle of the emission shape. Note that latitude
 * here is what is typically called colatitude, the zenith or phi, the
 * angle from the z-axis. Similarly longitude is the angle in the
 * xy-plane from the x-axis, often referred to as the azimuth or
 * theta. Both values default to zero, which translates to no change
 * relative to the emission shape's direction. Both values are
 * animatable. */

@property CGFloat emissionLatitude;
@property CGFloat emissionLongitude;

/* An angle (in radians) defining a cone around the emission angle.
 * Emitted objects are uniformly distributed across this cone. Defaults
 * to zero.  Animatable. */

@property CGFloat emissionRange;

/* The initial mean velocity of each emitted object, and its range. Both
 * values default to zero. Animatable. */

@property CGFloat velocity;
@property CGFloat velocityRange;

/* The acceleration vector applied to emitted objects. Defaults to
 * (0, 0, 0). Animatable. */

@property CGFloat xAcceleration;
@property CGFloat yAcceleration;
@property CGFloat zAcceleration;

/* The scale factor applied to each emitted object, defined as mean and
 * range about the mean. Scale defaults to one, range to zero.
 * Animatable. */

@property CGFloat scale;
@property CGFloat scaleRange;
@property CGFloat scaleSpeed;

/* The rotation speed applied to each emitted object, defined as mean
 * and range about the mean. Defaults to zero. Animatable. */

@property CGFloat spin;
@property CGFloat spinRange;

/* The mean color of each emitted object, and the range from that mean
 * color. `color' defaults to opaque white, `colorRange' to (0, 0, 0,
 * 0). Animatable. */

@property(nullable) CGColorRef color;

@property float redRange;
@property float greenRange;
@property float blueRange;
@property float alphaRange;

/* The speed at which color components of emitted objects change over
 * their lifetime, defined as the rate of change per second. Defaults
 * to (0, 0, 0, 0). Animatable. */

@property float redSpeed;
@property float greenSpeed;
@property float blueSpeed;
@property float alphaSpeed;

/* The cell contents, typically a CGImageRef. Defaults to nil.
 * Animatable. */

@property(nullable, strong) id contents;

/* The sub-rectangle of the contents image that will be drawn. See
 * CALayer.h for more details. Defaults to the unit rectangle [0 0 1 1].
 * Animatable. */

@property CGRect contentsRect;

/* Defines the scale factor applied to the contents of the cell. See
 * CALayer.h for more details. */

@property CGFloat contentsScale;

/* The filter parameters used when rendering the `contents' image. See
 * CALayer.h for more details. */

@property(copy) NSString *minificationFilter;
@property(copy) NSString *magnificationFilter;
@property float minificationFilterBias;

/* An array containing the sub-cells of this cell, or nil (the default
 * value). When non-nil each particle emitted by the cell will act as
 * an emitter for each of the cell's sub-cells. The emission point is
 * the current particle position and the emission angle is relative to
 * the current direction of the particle. Animatable. */

@property(nullable, copy) NSArray<CAEmitterCell *> *emitterCells;

/* Inherited attributes similar to in layers. */

@property(nullable, copy) NSDictionary *style;

@end

NS_ASSUME_NONNULL_END
// ==========  QuartzCore.framework/Headers/CAShapeLayer.h
/* CoreAnimation - CAShapeLayer.h

   Copyright (c) 2008-2018, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CALayer.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString * CAShapeLayerFillRule NS_TYPED_ENUM;
typedef NSString * CAShapeLayerLineJoin NS_TYPED_ENUM;
typedef NSString * CAShapeLayerLineCap NS_TYPED_ENUM;

/* The shape layer draws a cubic Bezier spline in its coordinate space.
 *
 * The spline is described using a CGPath object and may have both fill
 * and stroke components (in which case the stroke is composited over
 * the fill). The shape as a whole is composited between the layer's
 * contents and its first sublayer.
 *
 * The path object may be animated using any of the concrete subclasses
 * of CAPropertyAnimation. Paths will interpolate as a linear blend of
 * the "on-line" points; "off-line" points may be interpolated
 * non-linearly (e.g. to preserve continuity of the curve's
 * derivative). If the two paths have a different number of control
 * points or segments the results are undefined.
 *
 * The shape will be drawn antialiased, and whenever possible it will
 * be mapped into screen space before being rasterized to preserve
 * resolution independence. (However, certain kinds of image processing
 * operations, e.g. CoreImage filters, applied to the layer or its
 * ancestors may force rasterization in a local coordinate space.)
 *
 * Note: rasterization may favor speed over accuracy, e.g. pixels with
 * multiple intersecting path segments may not give exact results. */

API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0))
@interface CAShapeLayer : CALayer

/* The path defining the shape to be rendered. If the path extends
 * outside the layer bounds it will not automatically be clipped to the
 * layer, only if the normal layer masking rules cause that. Upon
 * assignment the path is copied. Defaults to null. Animatable.
 * (Note that although the path property is animatable, no implicit
 * animation will be created when the property is changed.) */

@property(nullable) CGPathRef path;

/* The color to fill the path, or nil for no fill. Defaults to opaque
 * black. Animatable. */

@property(nullable) CGColorRef fillColor;

/* The fill rule used when filling the path. Options are `non-zero' and
 * `even-odd'. Defaults to `non-zero'. */

@property(copy) CAShapeLayerFillRule fillRule;

/* The color to fill the path's stroked outline, or nil for no stroking.
 * Defaults to nil. Animatable. */

@property(nullable) CGColorRef strokeColor;

/* These values define the subregion of the path used to draw the
 * stroked outline. The values must be in the range [0,1] with zero
 * representing the start of the path and one the end. Values in
 * between zero and one are interpolated linearly along the path
 * length. strokeStart defaults to zero and strokeEnd to one. Both are
 * animatable. */

@property CGFloat strokeStart;
@property CGFloat strokeEnd;

/* The line width used when stroking the path. Defaults to one.
 * Animatable. */

@property CGFloat lineWidth;

/* The miter limit used when stroking the path. Defaults to ten.
 * Animatable. */

@property CGFloat miterLimit;

/* The cap style used when stroking the path. Options are `butt', `round'
 * and `square'. Defaults to `butt'. */

@property(copy) CAShapeLayerLineCap lineCap;

/* The join style used when stroking the path. Options are `miter', `round'
 * and `bevel'. Defaults to `miter'. */

@property(copy) CAShapeLayerLineJoin lineJoin;

/* The phase of the dashing pattern applied when creating the stroke.
 * Defaults to zero. Animatable. */

@property CGFloat lineDashPhase;

/* The dash pattern (an array of NSNumbers) applied when creating the
 * stroked version of the path. Defaults to nil. */

@property(nullable, copy) NSArray<NSNumber *> *lineDashPattern;

@end

/* `fillRule' values. */

CA_EXTERN CAShapeLayerFillRule const kCAFillRuleNonZero
    API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAShapeLayerFillRule const kCAFillRuleEvenOdd
    API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));

/* `lineJoin' values. */

CA_EXTERN CAShapeLayerLineJoin const kCALineJoinMiter
    API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAShapeLayerLineJoin const kCALineJoinRound
    API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAShapeLayerLineJoin const kCALineJoinBevel
    API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));

/* `lineCap' values. */

CA_EXTERN CAShapeLayerLineCap const kCALineCapButt
    API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAShapeLayerLineCap const kCALineCapRound
    API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAShapeLayerLineCap const kCALineCapSquare
    API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));

NS_ASSUME_NONNULL_END
// ==========  QuartzCore.framework/Headers/CAValueFunction.h
/* CoreAnimation - CAValueFunction.h

   Copyright (c) 2008-2018, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CABase.h>
#import <Foundation/NSObject.h>

typedef NSString * CAValueFunctionName NS_TYPED_ENUM;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0))
@interface CAValueFunction : NSObject <NSSecureCoding>
{
@protected
  NSString *_string;
  void *_impl;
}

+ (nullable instancetype)functionWithName:(CAValueFunctionName)name;

@property(readonly) CAValueFunctionName name;

@end

/** Value function names. **/

/* The `rotateX', `rotateY', `rotateZ' functions take a single input
 * value in radians, and construct a 4x4 matrix representing the
 * corresponding rotation matrix. */

CA_EXTERN CAValueFunctionName const kCAValueFunctionRotateX
    API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAValueFunctionName const kCAValueFunctionRotateY
    API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAValueFunctionName const kCAValueFunctionRotateZ
    API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));

/* The `scale' function takes three input values and constructs a
 * 4x4 matrix representing the corresponding scale matrix. */

CA_EXTERN CAValueFunctionName const kCAValueFunctionScale
    API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));

/* The `scaleX', `scaleY', `scaleZ' functions take a single input value
 * and construct a 4x4 matrix representing the corresponding scaling
 * matrix. */

CA_EXTERN CAValueFunctionName const kCAValueFunctionScaleX
    API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAValueFunctionName const kCAValueFunctionScaleY
    API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAValueFunctionName const kCAValueFunctionScaleZ
    API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));

/* The `translate' function takes three input values and constructs a
 * 4x4 matrix representing the corresponding scale matrix. */

CA_EXTERN CAValueFunctionName const kCAValueFunctionTranslate
    API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));

/* The `translateX', `translateY', `translateZ' functions take a single
 * input value and construct a 4x4 matrix representing the corresponding
 * translation matrix. */

CA_EXTERN CAValueFunctionName const kCAValueFunctionTranslateX
    API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAValueFunctionName const kCAValueFunctionTranslateY
    API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAValueFunctionName const kCAValueFunctionTranslateZ
    API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));

NS_ASSUME_NONNULL_END
// ==========  QuartzCore.framework/Headers/CAMetalLayer.h
/* CoreAnimation - CAMetalLayer.h

   Copyright (c) 2013-2018, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CALayer.h>
#import <Metal/MTLPixelFormat.h>
#import <Metal/MTLDrawable.h>

@protocol MTLDevice;
@protocol MTLTexture;
@protocol MTLDrawable;

@class CAMetalLayer;

NS_ASSUME_NONNULL_BEGIN

/* CAMetalDrawable represents a displayable buffer that vends an object
 * that conforms to the MTLTexture protocol that may be used to create
 * a render target for Metal.
 *
 * Note: CAMetalLayer maintains an internal pool of textures used for
 * display. In order for a texture to be re-used for a new CAMetalDrawable,
 * any prior CAMetalDrawable must have been deallocated and another
 * CAMetalDrawable presented. */

@protocol CAMetalDrawable <MTLDrawable>

/* This is an object that conforms to the MTLTexture protocol and will
 * typically be used to create an MTLRenderTargetDescriptor. */

@property(readonly) id<MTLTexture> texture;

/* This is the CAMetalLayer responsible for displaying the drawable */

@property(readonly) CAMetalLayer *layer;

@end

/* Note: The default value of the `opaque' property for CAMetalLayer
 * instances is true. */

API_AVAILABLE(macos(10.11), ios(8.0), watchos(2.0), tvos(9.0))
@interface CAMetalLayer : CALayer
{
@private
  struct _CAMetalLayerPrivate *_priv;
}

/* This property determines which MTLDevice the MTLTexture objects for
 * the drawables will be created from.
 * On iOS this defaults to MTLCreateSystemDefaultDevice().
 * On macOS this defaults to nil and must be set explicitly before asking for
 * the first drawable. */

@property(nullable, retain) id<MTLDevice> device;

/* This property returns the preferred MTLDevice for this CAMetalLayer. */

@property(nullable, readonly) id<MTLDevice> preferredDevice
  API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/* This property controls the pixel format of the MTLTexture objects.
 * The two supported values are MTLPixelFormatBGRA8Unorm and
 * MTLPixelFormatBGRA8Unorm_sRGB. */

@property MTLPixelFormat pixelFormat;

/* This property controls whether or not the returned drawables'
 * MTLTextures may only be used for framebuffer attachments (YES) or
 * whether they may also be used for texture sampling and pixel
 * read/write operations (NO). A value of YES allows CAMetalLayer to
 * allocate the MTLTexture objects in ways that are optimized for display
 * purposes that makes them unsuitable for sampling. The recommended
 * value for most applications is YES. */

@property BOOL framebufferOnly;

/* This property controls the pixel dimensions of the returned drawable
 * objects. The most typical value will be the layer size multiplied by
 * the layer contentsScale property. */

@property CGSize drawableSize;

/* Get the swap queue's next available drawable. Always blocks until a drawable
 * is available. Can return nil under the following conditions:
 *     1) The layer has an invalid combination of drawable properties.
 *     2) All drawables in the swap queue are in-use and the 1 second timeout
 *        has elapsed. (except when `allowsNextDrawableTimeout' is set to NO)
 *     3) Process is out of memory. */

- (nullable id<CAMetalDrawable>)nextDrawable;

/* Controls the number maximum number of drawables in the swap queue. The
 * default value is 3. Values set outside of range [2, 3] are ignored and an
 * exception will be thrown. */

@property NSUInteger maximumDrawableCount
  API_AVAILABLE(macos(10.13.2), ios(11.2), watchos(4.2), tvos(11.2));

/* When false (the default value) changes to the layer's render buffer
 * appear on-screen asynchronously to normal layer updates. When true,
 * changes to the MTL content are sent to the screen via the standard
 * CATransaction mechanisms. */

@property BOOL presentsWithTransaction;

/* The colorspace of the rendered frames. If nil, no colormatching occurs.
 * If non-nil, the rendered content will be colormatched to the colorspace of
 * the context containing this layer (typically the display's colorspace). */

@property (nullable) CGColorSpaceRef colorspace;



/* Controls if `-nextDrawable' is allowed to timeout after 1 second and return
 * nil if * the system does not have a free drawable available. The default
 * value is YES. If set to NO, then `-nextDrawable' will block forever until a
 * free drawable is available. */

@property BOOL allowsNextDrawableTimeout
  API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

@end

NS_ASSUME_NONNULL_END
// ==========  QuartzCore.framework/Headers/CATransaction.h
/* CoreAnimation - CATransaction.h

   Copyright (c) 2006-2018, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CABase.h>
#import <Foundation/NSObject.h>

/* Transactions are CoreAnimation's mechanism for batching multiple layer-
 * tree operations into atomic updates to the render tree. Every
 * modification to the layer tree requires a transaction to be part of.
 *
 * CoreAnimation supports two kinds of transactions, "explicit" transactions
 * and "implicit" transactions.
 *
 * Explicit transactions are where the programmer calls `[CATransaction
 * begin]' before modifying the layer tree, and `[CATransaction commit]'
 * afterwards.
 *
 * Implicit transactions are created automatically by CoreAnimation when the
 * layer tree is modified by a thread without an active transaction.
 * They are committed automatically when the thread's run-loop next
 * iterates. In some circumstances (i.e. no run-loop, or the run-loop
 * is blocked) it may be necessary to use explicit transactions to get
 * timely render tree updates. */

@class CAMediaTimingFunction;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
@interface CATransaction : NSObject

/* Begin a new transaction for the current thread; nests. */

+ (void)begin;

/* Commit all changes made during the current transaction. Raises an
 * exception if no current transaction exists. */

+ (void)commit;

/* Commits any extant implicit transaction. Will delay the actual commit
 * until any nested explicit transactions have completed. */

+ (void)flush;

/* Methods to lock and unlock the global lock. Layer methods automatically
 * obtain this while modifying shared state, but callers may need to lock
 * around multiple operations to ensure consistency. The lock is a
 * recursive spin-lock (i.e shouldn't be held for extended periods). */

+ (void)lock;
+ (void)unlock;

/* Accessors for the "animationDuration" per-thread transaction
 * property. Defines the default duration of animations added to
 * layers. Defaults to 1/4s. */

+ (CFTimeInterval)animationDuration;
+ (void)setAnimationDuration:(CFTimeInterval)dur;

/* Accessors for the "animationTimingFunction" per-thread transaction
 * property. The default value is nil, when set to a non-nil value any
 * animations added to layers will have this value set as their
 * "timingFunction" property. Added in Mac OS X 10.6. */

+ (nullable CAMediaTimingFunction *)animationTimingFunction;
+ (void)setAnimationTimingFunction:(nullable CAMediaTimingFunction *)function;

/* Accessors for the "disableActions" per-thread transaction property.
 * Defines whether or not the layer's -actionForKey: method is used to
 * find an action (aka. implicit animation) for each layer property
 * change. Defaults to NO, i.e. implicit animations enabled. */

+ (BOOL)disableActions;
+ (void)setDisableActions:(BOOL)flag;

/* Accessors for the "completionBlock" per-thread transaction property.
 * Once set to a non-nil value the block is guaranteed to be called (on
 * the main thread) as soon as all animations subsequently added by
 * this transaction group have completed (or been removed). If no
 * animations are added before the current transaction group is
 * committed (or the completion block is set to a different value), the
 * block will be invoked immediately. Added in Mac OS X 10.6. */

#if __BLOCKS__
+ (nullable void (^)(void))completionBlock;
+ (void)setCompletionBlock:(nullable void (^)(void))block;
#endif

/* Associate arbitrary keyed-data with the current transaction (i.e.
 * with the current thread).
 *
 * Nested transactions have nested data scope, i.e. reading a key
 * searches for the innermost scope that has set it, setting a key
 * always sets it in the innermost scope.
 *
 * Currently supported transaction properties include:
 * "animationDuration", "animationTimingFunction", "completionBlock",
 * "disableActions". See method declarations above for descriptions of
 * each property.
 *
 * Attempting to set a property to a type other than its document type
 * has an undefined result. */

+ (nullable id)valueForKey:(NSString *)key;
+ (void)setValue:(nullable id)anObject forKey:(NSString *)key;

@end

/** Transaction property ids. **/

CA_EXTERN NSString * const kCATransactionAnimationDuration
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN NSString * const kCATransactionDisableActions
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN NSString * const kCATransactionAnimationTimingFunction
    API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));
CA_EXTERN NSString * const kCATransactionCompletionBlock
    API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

NS_ASSUME_NONNULL_END
// ==========  QuartzCore.framework/Headers/CABase.h
/* CoreAnimation - CABase.h

   Copyright (c) 2006-2018, Apple Inc.
   All rights reserved. */

#ifndef CABASE_H
#define CABASE_H

/* Adapted from <CoreGraphics/CGBase.h> */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <float.h>

#include <CoreFoundation/CoreFoundation.h>

#if TARGET_OS_MAC
#include <CoreGraphics/CoreGraphics.h>
#endif

#include <os/availability.h>
#include <TargetConditionals.h>

#if TARGET_OS_OSX
# define CA_OSX_VERSION(v) ((v) > 0 && __MAC_OS_X_VERSION_MAX_ALLOWED >= (v))
#else
# define CA_OSX_VERSION(v) (0)
#endif

#if TARGET_OS_IPHONE
# define CA_IOS_VERSION(v) ((v) > 0 && __IPHONE_OS_VERSION_MIN_REQUIRED >= (v))
#else
# define CA_IOS_VERSION(v) (0)
#endif

#if TARGET_OS_TV
# define CA_TV_VERSION(v) ((v) > 0 && __TV_OS_VERSION_MIN_REQUIRED >= (v))
#else
# define CA_TV_VERSION(v) (0)
#endif

#if TARGET_OS_WATCH
# define CA_WATCH_VERSION(v) ((v) > 0 && __WATCH_OS_VERSION_MIN_REQUIRED >= (v))
#else
# define CA_WATCH_VERSION(v) (0)
#endif

#ifdef __cplusplus
# define CA_EXTERN_C_BEGIN extern "C" {
# define CA_EXTERN_C_END   }
#else
# define CA_EXTERN_C_BEGIN
# define CA_EXTERN_C_END
#endif

#ifdef __GNUC__
# define CA_GNUC(major, minor) \
  (__GNUC__ > (major) || (__GNUC__ == (major) && __GNUC_MINOR__ >= (minor)))
#else
# define CA_GNUC(major, minor) 0
#endif

#ifndef CA_EXTERN
# define CA_EXTERN extern __attribute__((visibility("default")))
#endif

#ifndef CA_INLINE
# if defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#  define CA_INLINE static inline
# elif defined (__cplusplus)
#  define CA_INLINE static inline
# elif CA_GNUC (3, 0)
#  define CA_INLINE static __inline__ __attribute__ ((always_inline))
# else
#  define CA_INLINE static
# endif
#endif

#ifndef CA_HIDDEN
# if CA_GNUC (4,0)
#  define CA_HIDDEN __attribute__ ((visibility ("hidden")))
# else
#  define CA_HIDDEN /* no hidden */
# endif
#endif

#ifdef CA_BUILD_TESTABLE
#  define CA_TEST 1
#  define CA_TESTABLE CA_EXTERN
#  define CA_TESTABLE_CLASS __attribute__((visibility("default")))
#else
#  define CA_TEST 0
#  define CA_TESTABLE CA_HIDDEN
#  define CA_TESTABLE_CLASS CA_HIDDEN
#endif

#ifndef CA_PURE
# if CA_GNUC (3, 0)
#  define CA_PURE __attribute__ ((pure))
# else
#  define CA_PURE /* no pure */
# endif
#endif

#ifndef CA_CONST
# if CA_GNUC (3, 0)
#  define CA_CONST __attribute__ ((const))
# else
#  define CA_CONST /* no const */
# endif
#endif

#ifndef CA_NORETURN
# if CA_GNUC (3, 0)
#  define CA_NORETURN __attribute__ ((noreturn))
# else
#  define CA_NORETURN /* no noreturn */
# endif
#endif

#ifndef CA_MALLOC
# if CA_GNUC (3, 0)
#  define CA_MALLOC __attribute__ ((malloc))
# else
#  define CA_MALLOC /* no malloc */
# endif
#endif

#ifndef CA_WARN_UNUSED
# if CA_GNUC (3, 4)
#  define CA_WARN_UNUSED __attribute__ ((warn_unused_result))
# else
#  define CA_WARN_UNUSED /* no warn_unused */
# endif
#endif

#ifndef CA_WARN_DEPRECATED
# define CA_WARN_DEPRECATED 1
#endif

#ifndef CA_DEPRECATED
# if CA_GNUC (3, 0) && CA_WARN_DEPRECATED
#  define CA_DEPRECATED __attribute__ ((deprecated))
# else
#  define CA_DEPRECATED
# endif
#endif

#if defined(__has_attribute) && __has_attribute(objc_boxable)
# define CA_BOXABLE __attribute__((objc_boxable))
#else
# define CA_BOXABLE
#endif

CA_EXTERN_C_BEGIN

/* Returns the current CoreAnimation absolute time. This is the result of
 * calling mach_absolute_time () and converting the units to seconds. */

CA_EXTERN CFTimeInterval CACurrentMediaTime (void)
    API_AVAILABLE (macos(10.5), ios(2.0));

CA_EXTERN_C_END

#endif /* CABASE_H */
// ==========  QuartzCore.framework/Headers/CAGradientLayer.h
/* CoreAnimation - CAGradientLayer.h

   Copyright (c) 2008-2018, Apple Inc.
   All rights reserved. */

/* The gradient layer draws a color gradient over its background color,
 * filling the shape of the layer (i.e. including rounded corners). */

#import <QuartzCore/CALayer.h>
#import <QuartzCore/CAMediaTimingFunction.h>
#import <Foundation/NSArray.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString * CAGradientLayerType NS_TYPED_ENUM;

API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0))
@interface CAGradientLayer : CALayer

/* The array of CGColorRef objects defining the color of each gradient
 * stop. Defaults to nil. Animatable. */

@property(nullable, copy) NSArray *colors;

/* An optional array of NSNumber objects defining the location of each
 * gradient stop as a value in the range [0,1]. The values must be
 * monotonically increasing. If a nil array is given, the stops are
 * assumed to spread uniformly across the [0,1] range. When rendered,
 * the colors are mapped to the output colorspace before being
 * interpolated. Defaults to nil. Animatable. */

@property(nullable, copy) NSArray<NSNumber *> *locations;

/* The start and end points of the gradient when drawn into the layer's
 * coordinate space. The start point corresponds to the first gradient
 * stop, the end point to the last gradient stop. Both points are
 * defined in a unit coordinate space that is then mapped to the
 * layer's bounds rectangle when drawn. (I.e. [0,0] is the bottom-left
 * corner of the layer, [1,1] is the top-right corner.) The default values
 * are [.5,0] and [.5,1] respectively. Both are animatable. */

@property CGPoint startPoint;
@property CGPoint endPoint;

/* The kind of gradient that will be drawn. Currently, the only allowed
 * values are `axial' (the default value), `radial', and `conic'. */

@property(copy) CAGradientLayerType type;

@end

/** `type' values. **/

CA_EXTERN CAGradientLayerType const kCAGradientLayerAxial
    API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));

/* Radial gradient. The gradient is defined as an ellipse with its
 * center at 'startPoint' and its width and height defined by
 * '(endPoint.x - startPoint.x) * 2' and '(endPoint.y - startPoint.y) *
 * 2' respectively. */

CA_EXTERN CAGradientLayerType const kCAGradientLayerRadial
    API_AVAILABLE(macos(10.6), ios(3.2), watchos(2.0), tvos(9.0));

/* Conic gradient. The gradient is centered at 'startPoint' and its 0-degrees
 * direction is defined by a vector spanned between 'startPoint' and
 * 'endPoint'. When 'startPoint' and 'endPoint' overlap the results are
 * undefined. The gradient's angle increases in the direction of rotation of
 * positive x-axis towards positive y-axis. */

CA_EXTERN CAGradientLayerType const kCAGradientLayerConic
    API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

NS_ASSUME_NONNULL_END
// ==========  QuartzCore.framework/Headers/CAAnimation.h
/* CoreAnimation - CAAnimation.h

   Copyright (c) 2006-2018, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CALayer.h>
#import <Foundation/NSObject.h>

@class NSArray, NSString, CAMediaTimingFunction, CAValueFunction;
@protocol CAAnimationDelegate;

NS_ASSUME_NONNULL_BEGIN

typedef NSString * CAAnimationCalculationMode NS_TYPED_ENUM;
typedef NSString * CAAnimationRotationMode NS_TYPED_ENUM;
typedef NSString * CATransitionType NS_TYPED_ENUM;
typedef NSString * CATransitionSubtype NS_TYPED_ENUM;

/** The base animation class. **/

API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
@interface CAAnimation : NSObject
    <NSSecureCoding, NSCopying, CAMediaTiming, CAAction>
{
@private
  void *_attr;
  uint32_t _flags;
}

/* Creates a new animation object. */

+ (instancetype)animation;

/* Animations implement the same property model as defined by CALayer.
 * See CALayer.h for more details. */

+ (nullable id)defaultValueForKey:(NSString *)key;
- (BOOL)shouldArchiveValueForKey:(NSString *)key;

/* A timing function defining the pacing of the animation. Defaults to
 * nil indicating linear pacing. */

@property(nullable, strong) CAMediaTimingFunction *timingFunction;

/* The delegate of the animation. This object is retained for the
 * lifetime of the animation object. Defaults to nil. See below for the
 * supported delegate methods. */

@property(nullable, strong) id <CAAnimationDelegate> delegate;

/* When true, the animation is removed from the render tree once its
 * active duration has passed. Defaults to YES. */

@property(getter=isRemovedOnCompletion) BOOL removedOnCompletion;

@end

/* Delegate methods for CAAnimation. */

@protocol CAAnimationDelegate <NSObject>
@optional

/* Called when the animation begins its active duration. */

- (void)animationDidStart:(CAAnimation *)anim;

/* Called when the animation either completes its active duration or
 * is removed from the object it is attached to (i.e. the layer). 'flag'
 * is true if the animation reached the end of its active duration
 * without being removed. */

- (void)animationDidStop:(CAAnimation *)anim finished:(BOOL)flag;

@end


/** Subclass for property-based animations. **/

API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
@interface CAPropertyAnimation : CAAnimation

/* Creates a new animation object with its `keyPath' property set to
 * 'path'. */

+ (instancetype)animationWithKeyPath:(nullable NSString *)path;

/* The key-path describing the property to be animated. */

@property(nullable, copy) NSString *keyPath;

/* When true the value specified by the animation will be "added" to
 * the current presentation value of the property to produce the new
 * presentation value. The addition function is type-dependent, e.g.
 * for affine transforms the two matrices are concatenated. Defaults to
 * NO. */

@property(getter=isAdditive) BOOL additive;

/* The `cumulative' property affects how repeating animations produce
 * their result. If true then the current value of the animation is the
 * value at the end of the previous repeat cycle, plus the value of the
 * current repeat cycle. If false, the value is simply the value
 * calculated for the current repeat cycle. Defaults to NO. */

@property(getter=isCumulative) BOOL cumulative;

/* If non-nil a function that is applied to interpolated values
 * before they are set as the new presentation value of the animation's
 * target property. Defaults to nil. */

@property(nullable, strong) CAValueFunction *valueFunction;

@end


/** Subclass for basic (single-keyframe) animations. **/

API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
@interface CABasicAnimation : CAPropertyAnimation

/* The objects defining the property values being interpolated between.
 * All are optional, and no more than two should be non-nil. The object
 * type should match the type of the property being animated (using the
 * standard rules described in CALayer.h). The supported modes of
 * animation are:
 *
 * - both `fromValue' and `toValue' non-nil. Interpolates between
 * `fromValue' and `toValue'.
 *
 * - `fromValue' and `byValue' non-nil. Interpolates between
 * `fromValue' and `fromValue' plus `byValue'.
 *
 * - `byValue' and `toValue' non-nil. Interpolates between `toValue'
 * minus `byValue' and `toValue'.
 *
 * - `fromValue' non-nil. Interpolates between `fromValue' and the
 * current presentation value of the property.
 *
 * - `toValue' non-nil. Interpolates between the layer's current value
 * of the property in the render tree and `toValue'.
 *
 * - `byValue' non-nil. Interpolates between the layer's current value
 * of the property in the render tree and that plus `byValue'. */

@property(nullable, strong) id fromValue;
@property(nullable, strong) id toValue;
@property(nullable, strong) id byValue;

@end


/** General keyframe animation class. **/

API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
@interface CAKeyframeAnimation : CAPropertyAnimation

/* An array of objects providing the value of the animation function for
 * each keyframe. */

@property(nullable, copy) NSArray *values;

/* An optional path object defining the behavior of the animation
 * function. When non-nil overrides the `values' property. Each point
 * in the path except for `moveto' points defines a single keyframe for
 * the purpose of timing and interpolation. Defaults to nil. For
 * constant velocity animation along the path, `calculationMode' should
 * be set to `paced'. Upon assignment the path is copied. */

@property(nullable) CGPathRef path;

/* An optional array of `NSNumber' objects defining the pacing of the
 * animation. Each time corresponds to one value in the `values' array,
 * and defines when the value should be used in the animation function.
 * Each value in the array is a floating point number in the range
 * [0,1]. */

@property(nullable, copy) NSArray<NSNumber *> *keyTimes;

/* An optional array of CAMediaTimingFunction objects. If the `values' array
 * defines n keyframes, there should be n-1 objects in the
 * `timingFunctions' array. Each function describes the pacing of one
 * keyframe to keyframe segment. */

@property(nullable, copy) NSArray<CAMediaTimingFunction *> *timingFunctions;

/* The "calculation mode". Possible values are `discrete', `linear',
 * `paced', `cubic' and `cubicPaced'. Defaults to `linear'. When set to
 * `paced' or `cubicPaced' the `keyTimes' and `timingFunctions'
 * properties of the animation are ignored and calculated implicitly. */

@property(copy) CAAnimationCalculationMode calculationMode;

/* For animations with the cubic calculation modes, these properties
 * provide control over the interpolation scheme. Each keyframe may
 * have a tension, continuity and bias value associated with it, each
 * in the range [-1, 1] (this defines a Kochanek-Bartels spline, see
 * http://en.wikipedia.org/wiki/Kochanek-Bartels_spline).
 *
 * The tension value controls the "tightness" of the curve (positive
 * values are tighter, negative values are rounder). The continuity
 * value controls how segments are joined (positive values give sharp
 * corners, negative values give inverted corners). The bias value
 * defines where the curve occurs (positive values move the curve before
 * the control point, negative values move it after the control point).
 *
 * The first value in each array defines the behavior of the tangent to
 * the first control point, the second value controls the second
 * point's tangents, and so on. Any unspecified values default to zero
 * (giving a Catmull-Rom spline if all are unspecified). */

@property(nullable, copy) NSArray<NSNumber *> *tensionValues;
@property(nullable, copy) NSArray<NSNumber *> *continuityValues;
@property(nullable, copy) NSArray<NSNumber *> *biasValues;

/* Defines whether or objects animating along paths rotate to match the
 * path tangent. Possible values are `auto' and `autoReverse'. Defaults
 * to nil. The effect of setting this property to a non-nil value when
 * no path object is supplied is undefined. `autoReverse' rotates to
 * match the tangent plus 180 degrees. */

@property(nullable, copy) CAAnimationRotationMode rotationMode;

@end

/* `calculationMode' strings. */

CA_EXTERN CAAnimationCalculationMode const kCAAnimationLinear
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAAnimationCalculationMode const kCAAnimationDiscrete
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAAnimationCalculationMode const kCAAnimationPaced
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAAnimationCalculationMode const kCAAnimationCubic
    API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAAnimationCalculationMode const kCAAnimationCubicPaced
    API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));

/* `rotationMode' strings. */

CA_EXTERN CAAnimationRotationMode const kCAAnimationRotateAuto
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CAAnimationRotationMode const kCAAnimationRotateAutoReverse
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/** Subclass for mass-spring animations. */

API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0))
@interface CASpringAnimation : CABasicAnimation

/* The mass of the object attached to the end of the spring. Must be greater
   than 0. Defaults to one. */

@property CGFloat mass;

/* The spring stiffness coefficient. Must be greater than 0.
 * Defaults to 100. */

@property CGFloat stiffness;

/* The damping coefficient. Must be greater than or equal to 0.
 * Defaults to 10. */

@property CGFloat damping;

/* The initial velocity of the object attached to the spring. Defaults
 * to zero, which represents an unmoving object. Negative values
 * represent the object moving away from the spring attachment point,
 * positive values represent the object moving towards the spring
 * attachment point. */

@property CGFloat initialVelocity;

/* Returns the estimated duration required for the spring system to be
 * considered at rest. The duration is evaluated for the current animation
 * parameters. */

@property(readonly) CFTimeInterval settlingDuration;

@end

/** Transition animation subclass. **/

API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
@interface CATransition : CAAnimation

/* The name of the transition. Current legal transition types include
 * `fade', `moveIn', `push' and `reveal'. Defaults to `fade'. */

@property(copy) CATransitionType type;

/* An optional subtype for the transition. E.g. used to specify the
 * transition direction for motion-based transitions, in which case
 * the legal values are `fromLeft', `fromRight', `fromTop' and
 * `fromBottom'. */

@property(nullable, copy) CATransitionSubtype subtype;

/* The amount of progress through to the transition at which to begin
 * and end execution. Legal values are numbers in the range [0,1].
 * `endProgress' must be greater than or equal to `startProgress'.
 * Default values are 0 and 1 respectively. */

@property float startProgress;
@property float endProgress;

@end

/* Common transition types. */

CA_EXTERN CATransitionType const kCATransitionFade
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CATransitionType const kCATransitionMoveIn
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CATransitionType const kCATransitionPush
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CATransitionType const kCATransitionReveal
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Common transition subtypes. */

CA_EXTERN CATransitionSubtype const kCATransitionFromRight
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CATransitionSubtype const kCATransitionFromLeft
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CATransitionSubtype const kCATransitionFromTop
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
CA_EXTERN CATransitionSubtype const kCATransitionFromBottom
    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));


/** Animation subclass for grouped animations. **/

API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
@interface CAAnimationGroup : CAAnimation

/* An array of CAAnimation objects. Each member of the array will run
 * concurrently in the time space of the parent animation using the
 * normal rules. */

@property(nullable, copy) NSArray<CAAnimation *> *animations;

@end

NS_ASSUME_NONNULL_END
