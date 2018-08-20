// ==========  MapKit.framework/Headers/MKGeodesicPolyline.h
//
//  MKGeodesicPolyline.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKPolyline.h>

NS_ASSUME_NONNULL_BEGIN

/*
 An MKGeodesicPolyline follows the shortest path along the surface of the earth,
 which may appear as a curved line when drawn on the projected MKMapView.
 */
MK_CLASS_AVAILABLE(10_9, 7_0) __WATCHOS_PROHIBITED
@interface MKGeodesicPolyline : MKPolyline

+ (instancetype)polylineWithPoints:(MKMapPoint *)points count:(NSUInteger)count;
+ (instancetype)polylineWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count;

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKPolygon.h
//
//  MKPolygon.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKMultiPoint.h>
#import <MapKit/MKOverlay.h>

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 4_0) __WATCHOS_PROHIBITED
@interface MKPolygon : MKMultiPoint <MKOverlay>

+ (instancetype)polygonWithPoints:(MKMapPoint *)points count:(NSUInteger)count;
+ (instancetype)polygonWithPoints:(MKMapPoint *)points count:(NSUInteger)count interiorPolygons:(nullable NSArray<MKPolygon *> *)interiorPolygons;

+ (instancetype)polygonWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count;
+ (instancetype)polygonWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count interiorPolygons:(nullable NSArray<MKPolygon *> *)interiorPolygons;

@property (readonly, nullable) NSArray<MKPolygon *> *interiorPolygons;

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKMapCamera.h
//
//  MKMapCamera.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MKFoundation.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 7_0) __WATCHOS_PROHIBITED
@interface MKMapCamera : NSObject <NSSecureCoding, NSCopying>

@property (nonatomic) CLLocationCoordinate2D centerCoordinate;
@property (nonatomic) CLLocationDirection heading;
@property (nonatomic) CGFloat pitch; // In degrees where 0 is looking straight down. Pitch may be clamped to an appropriate value.
@property (nonatomic) CLLocationDistance altitude;

+ (instancetype)camera;

+ (instancetype)cameraLookingAtCenterCoordinate:(CLLocationCoordinate2D)centerCoordinate
                              fromEyeCoordinate:(CLLocationCoordinate2D)eyeCoordinate
                                    eyeAltitude:(CLLocationDistance)eyeAltitude;

+ (instancetype)cameraLookingAtCenterCoordinate:(CLLocationCoordinate2D)centerCoordinate
                                   fromDistance:(CLLocationDistance)distance
                                          pitch:(CGFloat)pitch
                                        heading:(CLLocationDirection)heading NS_AVAILABLE(10_11, 9_0);


@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKLocalSearch.h
//
//  MKLocalSearch.h
//  MapKit
//
//  Copyright (c) 2012-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MKLocalSearchRequest;
@class MKLocalSearchResponse;

typedef void (^MKLocalSearchCompletionHandler)(MKLocalSearchResponse * __nullable response, NSError * __nullable error);

MK_CLASS_AVAILABLE(10_9, 6_1) __WATCHOS_PROHIBITED
@interface MKLocalSearch : NSObject

// The request will be copied during initialization, so any changes made to the request
// after this method returns do not affect the request used in -startWithCompletionHandler:
- (instancetype)initWithRequest:(MKLocalSearchRequest *)request NS_DESIGNATED_INITIALIZER;

// Any calls to -startWithCompletionHandler: while -[MKLocalSearch isSearching] will fail.
// completionHandler will be called on the main queue
- (void)startWithCompletionHandler:(MKLocalSearchCompletionHandler)completionHandler;
- (void)cancel;

@property (nonatomic, readonly, getter=isSearching) BOOL searching;

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKCircleRenderer.h
//
//  MKCircleRenderer.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKOverlayPathRenderer.h>
#import <MapKit/MKCircle.h>

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 7_0) __WATCHOS_PROHIBITED
@interface MKCircleRenderer : MKOverlayPathRenderer

- (instancetype)initWithCircle:(MKCircle *)circle;

@property (nonatomic, readonly) MKCircle *circle;

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKPolyline.h
//
//  MKPolyline.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKMultiPoint.h>
#import <MapKit/MKOverlay.h>
#import <MapKit/MKFoundation.h>

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 4_0) __WATCHOS_PROHIBITED
@interface MKPolyline : MKMultiPoint <MKOverlay>

+ (instancetype)polylineWithPoints:(MKMapPoint *)points count:(NSUInteger)count;
+ (instancetype)polylineWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count;

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKPolylineRenderer.h
//
//  MKPolylineRenderer.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKOverlayPathRenderer.h>
#import <MapKit/MKPolyline.h>

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 7_0) __WATCHOS_PROHIBITED
@interface MKPolylineRenderer : MKOverlayPathRenderer

- (instancetype)initWithPolyline:(MKPolyline *)polyline;

@property (nonatomic, readonly) MKPolyline *polyline;

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKReverseGeocoder.h
//
//  MKReverseGeocoder.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CLLocation.h>
#import <MapKit/MKTypes.h>
#import <MapKit/MKFoundation.h>
#import <MapKit/MKPlacemark.h>

@protocol MKReverseGeocoderDelegate;

// MKReverseGeocoder is now deprecated.
// Use CLGeocoder in CoreLocation instead.
MK_CLASS_DEPRECATED(NA, NA, 3_0, 5_0) __WATCHOS_PROHIBITED
@interface MKReverseGeocoder : NSObject

- (instancetype)initWithCoordinate:(CLLocationCoordinate2D)coordinate NS_DEPRECATED_IOS(3_0,5_0);


// A MKReverseGeocoder object should only be started once.
- (void)start NS_DEPRECATED_IOS(3_0,5_0);
- (void)cancel NS_DEPRECATED_IOS(3_0,5_0);

@property (nonatomic, weak) id<MKReverseGeocoderDelegate> delegate    NS_DEPRECATED_IOS(3_0,5_0);
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate       NS_DEPRECATED_IOS(3_0,5_0);
@property (nonatomic, readonly) MKPlacemark *placemark                  NS_DEPRECATED_IOS(3_2,5_0);
@property (nonatomic, readonly, getter=isQuerying) BOOL querying        NS_DEPRECATED_IOS(3_0,5_0);

@end

MK_CLASS_DEPRECATED(NA, NA, 3_0, 5_0) __WATCHOS_PROHIBITED
@protocol MKReverseGeocoderDelegate <NSObject>
@required
- (void)reverseGeocoder:(MKReverseGeocoder *)geocoder didFindPlacemark:(MKPlacemark *)placemark NS_DEPRECATED_IOS(3_0,5_0);
// There are at least two types of errors:
//   - Errors sent up from the underlying connection (temporary condition)
//   - Result not found errors (permanent condition).  The result not found errors
//     will have the domain MKErrorDomain and the code MKErrorPlacemarkNotFound
- (void)reverseGeocoder:(MKReverseGeocoder *)geocoder didFailWithError:(NSError *)error NS_DEPRECATED_IOS(3_0,5_0);
@end
// ==========  MapKit.framework/Headers/MKPolygonRenderer.h
//
//  MKPolygonRenderer.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKOverlayPathRenderer.h>
#import <MapKit/MKPolygon.h>

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 7_0) __WATCHOS_PROHIBITED
@interface MKPolygonRenderer : MKOverlayPathRenderer

- (instancetype)initWithPolygon:(MKPolygon *)polygon;
@property (nonatomic, readonly) MKPolygon *polygon;

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKOverlayPathView.h
//
//  MKOverlayPathView.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <MapKit/MKOverlayView.h>
#import <MapKit/MKFoundation.h>

// Prefer MKOverlayPathRenderer
MK_CLASS_AVAILABLE(NA, 4_0) __WATCHOS_PROHIBITED
@interface MKOverlayPathView : MKOverlayView

@property (strong) UIColor *fillColor NS_DEPRECATED_IOS(4_0, 7_0);
@property (strong) UIColor *strokeColor NS_DEPRECATED_IOS(4_0, 7_0);

@property CGFloat lineWidth NS_DEPRECATED_IOS(4_0, 7_0); // defaults to 0, which is MKRoadWidthAtZoomScale(currentZoomScale)
@property CGLineJoin lineJoin NS_DEPRECATED_IOS(4_0, 7_0); // defaults to kCGLineJoinRound
@property CGLineCap lineCap NS_DEPRECATED_IOS(4_0, 7_0); // defaults to kCGLineCapRound
@property CGFloat miterLimit NS_DEPRECATED_IOS(4_0, 7_0); // defaults to 10
@property CGFloat lineDashPhase NS_DEPRECATED_IOS(4_0, 7_0); // defaults to 0
@property (copy) NSArray *lineDashPattern NS_DEPRECATED_IOS(4_0, 7_0); // an array of NSNumbers, defaults to nil

// subclassers should override this to create a path and then set it on
// themselves with self.path = newPath;
- (void)createPath NS_DEPRECATED_IOS(4_0, 7_0);
// returns cached path or calls createPath if path has not yet been created
@property CGPathRef path NS_DEPRECATED_IOS(4_0, 7_0); // path will be retained
- (void)invalidatePath NS_DEPRECATED_IOS(4_0, 7_0);

// subclassers may override these
- (void)applyStrokePropertiesToContext:(CGContextRef)context
                           atZoomScale:(MKZoomScale)zoomScale NS_DEPRECATED_IOS(4_0, 7_0);
- (void)applyFillPropertiesToContext:(CGContextRef)context
                         atZoomScale:(MKZoomScale)zoomScale NS_DEPRECATED_IOS(4_0, 7_0);
- (void)strokePath:(CGPathRef)path inContext:(CGContextRef)context NS_DEPRECATED_IOS(4_0, 7_0);
- (void)fillPath:(CGPathRef)path inContext:(CGContextRef)context NS_DEPRECATED_IOS(4_0, 7_0);

@end
// ==========  MapKit.framework/Headers/MKCircleView.h
//
//  MKCircleView.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MKCircle.h>
#import <MapKit/MKFoundation.h>
#import <MapKit/MKOverlayPathView.h>

// Prefer MKCircleRenderer
MK_CLASS_AVAILABLE(NA, 4_0) __WATCHOS_PROHIBITED
@interface MKCircleView : MKOverlayPathView

- (instancetype)initWithCircle:(MKCircle *)circle NS_DEPRECATED_IOS(4_0, 7_0);

@property (nonatomic, readonly) MKCircle *circle NS_DEPRECATED_IOS(4_0, 7_0);

@end
// ==========  MapKit.framework/Headers/MKAnnotationView.h
//
//  MKAnnotationView.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

// Post this notification to re-query callout information.
MK_EXTERN NSString * const MKAnnotationCalloutInfoDidChangeNotification;

typedef NS_ENUM(NSUInteger, MKAnnotationViewDragState) {
    MKAnnotationViewDragStateNone = 0,      // View is at rest, sitting on the map.
    MKAnnotationViewDragStateStarting,      // View is beginning to drag (e.g. pin lift)
    MKAnnotationViewDragStateDragging,      // View is dragging ("lift" animations are complete)
    MKAnnotationViewDragStateCanceling,     // View was not dragged and should return to its starting position (e.g. pin drop)
    MKAnnotationViewDragStateEnding         // View was dragged, new coordinate is set and view should return to resting position (e.g. pin drop)
} NS_ENUM_AVAILABLE(10_9, 4_0) __WATCHOS_PROHIBITED;

@protocol MKAnnotation;

#if TARGET_OS_IPHONE
MK_CLASS_AVAILABLE(NA, 3_0) __WATCHOS_PROHIBITED
@interface MKAnnotationView : UIView
#else
MK_CLASS_AVAILABLE(10_9, NA)
@interface MKAnnotationView : NSView
#endif

- (instancetype)initWithAnnotation:(nullable id <MKAnnotation>)annotation reuseIdentifier:(nullable NSString *)reuseIdentifier;

@property (nonatomic, readonly, nullable) NSString *reuseIdentifier;

// Classes that override must call super.
- (void)prepareForReuse;

@property (nonatomic, strong, nullable) id <MKAnnotation> annotation;

#if TARGET_OS_IPHONE
@property (nonatomic, strong, nullable) UIImage *image;
#else
@property (nonatomic, strong, nullable) NSImage *image;
#endif

// By default, the center of annotation view is placed over the coordinate of the annotation.
// centerOffset is the offset in screen points from the center of the annotion view.
@property (nonatomic) CGPoint centerOffset;

// calloutOffset is the offset in screen points from the top-middle of the annotation view, where the anchor of the callout should be shown.
@property (nonatomic) CGPoint calloutOffset;

#if !TARGET_OS_IPHONE
// leftCalloutOffset is the offset in screen points from the middle-left of the annotation view, where the anchor of the callout should be shown when oriented off the left side of the annotation view
@property (nonatomic) CGPoint leftCalloutOffset;

// rightCalloutOffset is the offset in screen points from the middle-right of the annotation view, where the anchor of the callout should be shown when oriented off the right side of the annotation view
@property (nonatomic) CGPoint rightCalloutOffset;
#endif

// Defaults to YES. If NO, ignores touch events and subclasses may draw differently.
@property (nonatomic, getter=isEnabled) BOOL enabled;

// Defaults to NO. This gets set/cleared automatically when touch enters/exits during tracking and cleared on up.
@property (nonatomic, getter=isHighlighted) BOOL highlighted;

// Defaults to NO. Becomes YES when tapped/clicked on in the map view.
@property (nonatomic, getter=isSelected) BOOL selected;
- (void)setSelected:(BOOL)selected animated:(BOOL)animated;

// If YES, a standard callout bubble will be shown when the annotation is selected.
// The annotation must have a title for the callout to be shown.
@property (nonatomic) BOOL canShowCallout;

// The left accessory view to be used in the standard callout.
#if TARGET_OS_IPHONE
@property (strong, nonatomic, nullable) UIView *leftCalloutAccessoryView;
#else
@property (strong, nonatomic, nullable) NSView *leftCalloutAccessoryView;
#endif

// The right accessory view to be used in the standard callout.
#if TARGET_OS_IPHONE
@property (strong, nonatomic, nullable) UIView *rightCalloutAccessoryView;
#else
@property (strong, nonatomic, nullable) NSView *rightCalloutAccessoryView;
#endif

// The detail accessory view to be used in the standard callout.
#if TARGET_OS_IPHONE
@property (nonatomic, strong, nullable) UIView *detailCalloutAccessoryView NS_AVAILABLE(10_11, 9_0);
#else
@property (nonatomic, strong, nullable) NSView *detailCalloutAccessoryView NS_AVAILABLE(10_11, 9_0);
#endif

// If YES and the underlying id<MKAnnotation> responds to setCoordinate:, 
// the user will be able to drag this annotation view around the map.
@property (nonatomic, getter=isDraggable) BOOL draggable NS_AVAILABLE(10_9, 4_0);

// Automatically set to MKAnnotationViewDragStateStarting, Canceling, and Ending when necessary.
// Implementer is responsible for transitioning to Dragging and None states as appropriate.
@property (nonatomic) MKAnnotationViewDragState dragState NS_AVAILABLE(10_9, 4_0);

// Developers targeting iOS 4.2 and after must use setDragState:animated: instead of setDragState:.
- (void)setDragState:(MKAnnotationViewDragState)newDragState animated:(BOOL)animated NS_AVAILABLE(10_9, 4_2);

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKAnnotation.h
//
//  MKAnnotation.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <CoreLocation/CoreLocation.h>
#import <MapKit/MKFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MKAnnotation <NSObject>

// Center latitude and longitude of the annotation view.
// The implementation of this property must be KVO compliant.
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;

@optional

// Title and subtitle for use by selection UI.
@property (nonatomic, readonly, copy, nullable) NSString *title;
@property (nonatomic, readonly, copy, nullable) NSString *subtitle;

// Called as a result of dragging an annotation view.
- (void)setCoordinate:(CLLocationCoordinate2D)newCoordinate NS_AVAILABLE(10_9, 4_0);

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKDistanceFormatter.h
//
//  MKDistanceFormatter.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <CoreLocation/CoreLocation.h>

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 7_0)
@interface MKDistanceFormatter : NSFormatter

// Convenience methods. MKDistanceFormatter also responds to the usual NSFormatter methods.
- (NSString *)stringFromDistance:(CLLocationDistance)distance;
- (CLLocationDistance)distanceFromString:(NSString *)distance; // Returns negative distance if distance string could not be parsed.

@property (copy, NS_NONATOMIC_IOSONLY, null_resettable) NSLocale *locale; // defaults to current locale

typedef NS_ENUM(NSUInteger, MKDistanceFormatterUnits) {
    MKDistanceFormatterUnitsDefault, // Let units depend on locale. Note that some locales use imperial measurements for distances but metric for everything else, so this is not identical to NSLocaleUsesMetricSystem.
    MKDistanceFormatterUnitsMetric,
    MKDistanceFormatterUnitsImperial,
    MKDistanceFormatterUnitsImperialWithYards
} NS_ENUM_AVAILABLE(10_9, 7_0);

@property (assign, NS_NONATOMIC_IOSONLY) MKDistanceFormatterUnits units;

typedef NS_ENUM(NSUInteger, MKDistanceFormatterUnitStyle) {
    MKDistanceFormatterUnitStyleDefault = 0,    // Whether to abbreviate depends on units, locale, and user interface language
    MKDistanceFormatterUnitStyleAbbreviated,    // Ex. km
    MKDistanceFormatterUnitStyleFull            // Ex. kilometers
} NS_ENUM_AVAILABLE(10_9, 7_0);

@property (assign, NS_NONATOMIC_IOSONLY) MKDistanceFormatterUnitStyle unitStyle;

@end

NS_ASSUME_NONNULL_END

// ==========  MapKit.framework/Headers/MKPlacemark.h
//
//  MKPlacemark.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKAnnotation.h>
#import <CoreLocation/CLLocation.h>
#import <CoreLocation/CLPlacemark.h>

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 3_0)
@interface MKPlacemark : CLPlacemark <MKAnnotation>

// An address dictionary is a dictionary in the same form as returned by 
// ABRecordCopyValue(person, kABPersonAddressProperty).
- (instancetype)initWithCoordinate:(CLLocationCoordinate2D)coordinate
                 addressDictionary:(nullable NSDictionary<NSString *, id> *)addressDictionary;

// To create an MKPlacemark from a CLPlacemark, call [MKPlacemark initWithPlacemark:] passing the CLPlacemark instance that is returned by CLGeocoder.
// See CLGeocoder.h and CLPlacemark.h in CoreLocation for more information.

@property (nonatomic, readonly, nullable) NSString *countryCode;

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKOverlay.h
//
//  MKOverlay.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKAnnotation.h>
#import <MapKit/MKTypes.h>
#import <MapKit/MKGeometry.h>

NS_ASSUME_NONNULL_BEGIN

__WATCHOS_PROHIBITED
@protocol MKOverlay <MKAnnotation>
@required

// From MKAnnotation, for areas this should return the centroid of the area.
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;

// boundingMapRect should be the smallest rectangle that completely contains the overlay.
// For overlays that span the 180th meridian, boundingMapRect should have either a negative MinX or a MaxX that is greater than MKMapSizeWorld.width.
@property (nonatomic, readonly) MKMapRect boundingMapRect;

@optional
// Implement intersectsMapRect to provide more precise control over when the view for the overlay should be shown.
// If omitted, MKMapRectIntersectsRect([overlay boundingRect], mapRect) will be used instead.
- (BOOL)intersectsMapRect:(MKMapRect)mapRect;

// If this method is implemented and returns YES, MKMapView may use it as a hint to skip loading or drawing the built in map content in the area covered by this overlay.
- (BOOL)canReplaceMapContent NS_AVAILABLE(10_9, 7_0);

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKMultiPoint.h
//
//  MKMultiPoint.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKShape.h>
#import <MapKit/MKGeometry.h>
#import <MapKit/MKTypes.h>

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 4_0) __WATCHOS_PROHIBITED
@interface MKMultiPoint : MKShape

- (MKMapPoint *)points NS_RETURNS_INNER_POINTER;
@property (nonatomic, readonly) NSUInteger pointCount;

// Unproject and copy points into the provided array of coordinates that
// must be large enough to hold range.length coordinates.
- (void)getCoordinates:(CLLocationCoordinate2D *)coords range:(NSRange)range;

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKDirectionsTypes.h
//
//  MKDirectionsTypes.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

typedef NS_OPTIONS(NSUInteger, MKDirectionsTransportType) {
    MKDirectionsTransportTypeAutomobile = 1 << 0,
    MKDirectionsTransportTypeWalking = 1 << 1,
    MKDirectionsTransportTypeTransit NS_ENUM_AVAILABLE(10_11, 9_0) = 1 << 2, // Only supported for ETA calculations
    MKDirectionsTransportTypeAny = 0x0FFFFFFF
} NS_ENUM_AVAILABLE(10_9, 7_0) __WATCHOS_PROHIBITED;
// ==========  MapKit.framework/Headers/MKCircle.h
//
//  MKCircle.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKShape.h>
#import <MapKit/MKOverlay.h>
#import <MapKit/MKGeometry.h>
#import <MapKit/MKFoundation.h>

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 4_0) __WATCHOS_PROHIBITED
@interface MKCircle : MKShape <MKOverlay>

+ (instancetype)circleWithCenterCoordinate:(CLLocationCoordinate2D)coord
                                  radius:(CLLocationDistance)radius;

+ (instancetype)circleWithMapRect:(MKMapRect)mapRect; // radius will be determined from MAX(width, height)

@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;
@property (nonatomic, readonly) CLLocationDistance radius;

@property (nonatomic, readonly) MKMapRect boundingMapRect; 

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKMapSnapshotOptions.h
//
//  MKMapSnapshotOptions.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>
#import <MapKit/MKTypes.h>
#import <MapKit/MKMapView.h>

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 7_0) __WATCHOS_PROHIBITED
@interface MKMapSnapshotOptions : NSObject <NSCopying>

@property (nonatomic, copy) MKMapCamera *camera;
@property (nonatomic, assign) MKMapRect mapRect;
@property (nonatomic, assign) MKCoordinateRegion region;
@property (nonatomic, assign) MKMapType mapType;

@property (nonatomic) BOOL showsPointsOfInterest; // Affects MKMapTypeStandard and MKMapTypeHybrid
@property (nonatomic) BOOL showsBuildings; // Affects MKMapTypeStandard

// The size of the image to create. Defaults to 256x256
#if TARGET_OS_IPHONE
@property (nonatomic, assign) CGSize size;
#else
@property (nonatomic, assign) NSSize size;
#endif

#if TARGET_OS_IPHONE
// Defaults to the device's screen scale
@property (nonatomic, assign) CGFloat scale;
#endif

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKPointAnnotation.h
//
//  MKPointAnnotation.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKShape.h>
#import <MapKit/MKFoundation.h>
#import <CoreLocation/CLLocation.h>

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 4_0) __WATCHOS_PROHIBITED
@interface MKPointAnnotation : MKShape

@property (nonatomic, assign) CLLocationCoordinate2D coordinate;

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKMapSnapshotter.h
//
//  MKMapSnapshotter.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

@class MKMapSnapshotOptions;
@class MKMapSnapshot;

NS_ASSUME_NONNULL_BEGIN

typedef void (^MKMapSnapshotCompletionHandler)(MKMapSnapshot * __nullable snapshot, NSError * __nullable error);

MK_CLASS_AVAILABLE(10_9, 7_0) __WATCHOS_PROHIBITED
@interface MKMapSnapshotter : NSObject

- (instancetype)initWithOptions:(MKMapSnapshotOptions *)options NS_DESIGNATED_INITIALIZER;

- (void)startWithCompletionHandler:(MKMapSnapshotCompletionHandler)completionHandler; // defaults to the main queue
- (void)startWithQueue:(dispatch_queue_t)queue completionHandler:(MKMapSnapshotCompletionHandler)completionHandler;
- (void)cancel;

@property (nonatomic, readonly, getter=isLoading) BOOL loading;

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKPinAnnotationView.h
//
//  MKPinAnnotationView.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKAnnotationView.h>

typedef NS_ENUM(NSUInteger, MKPinAnnotationColor) {
    MKPinAnnotationColorRed = 0,
    MKPinAnnotationColorGreen,
    MKPinAnnotationColorPurple
} NS_ENUM_DEPRECATED(10_9, 10_11, 3_0, 9_0, "Use MKPinAnnotationView's pinTintColor instead") __WATCHOS_PROHIBITED;

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 3_0) __WATCHOS_PROHIBITED
@interface MKPinAnnotationView : MKAnnotationView

#if TARGET_OS_IPHONE
+ (UIColor *)redPinColor NS_AVAILABLE(10_11, 9_0);
+ (UIColor *)greenPinColor NS_AVAILABLE(10_11, 9_0);
+ (UIColor *)purplePinColor NS_AVAILABLE(10_11, 9_0);
#else
+ (NSColor *)redPinColor NS_AVAILABLE(10_11, 9_0);
+ (NSColor *)greenPinColor NS_AVAILABLE(10_11, 9_0);
+ (NSColor *)purplePinColor NS_AVAILABLE(10_11, 9_0);
#endif

#if TARGET_OS_IPHONE
@property (NS_NONATOMIC_IOSONLY, strong, null_resettable) UIColor *pinTintColor NS_AVAILABLE(10_11, 9_0) UI_APPEARANCE_SELECTOR;
#else
@property (NS_NONATOMIC_IOSONLY, strong, null_resettable) NSColor *pinTintColor NS_AVAILABLE(10_11, 9_0);
#endif

@property (nonatomic) BOOL animatesDrop;

@property (nonatomic) MKPinAnnotationColor pinColor NS_DEPRECATED(10_9, 10_11, 3_0, 9_0, "Use pinTintColor instead");

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MapKit.h
//
//  MapKit.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

#import <MapKit/MKAnnotation.h>
#import <MapKit/MKDistanceFormatter.h>
#import <MapKit/MKGeometry.h>
#import <MapKit/MKMapItem.h>
#import <MapKit/MKPlacemark.h>

#if __has_include(<MapKit/MKMapView.h>)
#import <MapKit/MKAnnotationView.h>
#import <MapKit/MKMapView.h>
#import <MapKit/MKPinAnnotationView.h>
#import <MapKit/MKUserLocation.h>
#import <MapKit/MKOverlay.h>
#import <MapKit/MKShape.h>
#import <MapKit/MKPointAnnotation.h>
#import <MapKit/MKMultiPoint.h>
#import <MapKit/MKPolyline.h>
#import <MapKit/MKPolygon.h>
#import <MapKit/MKCircle.h>
#import <MapKit/MKGeodesicPolyline.h>
#import <MapKit/MKOverlayRenderer.h>
#import <MapKit/MKOverlayPathRenderer.h>
#import <MapKit/MKPolygonRenderer.h>
#import <MapKit/MKPolylineRenderer.h>
#import <MapKit/MKCircleRenderer.h>
#import <MapKit/MKLocalSearch.h>
#import <MapKit/MKLocalSearchRequest.h>
#import <MapKit/MKLocalSearchResponse.h>
#import <MapKit/MKDirectionsRequest.h>
#import <MapKit/MKDirections.h>
#import <MapKit/MKDirectionsResponse.h>
#import <MapKit/MKMapSnapshotOptions.h>
#import <MapKit/MKMapSnapshotter.h>
#import <MapKit/MKMapSnapshot.h>
#import <MapKit/MKTileOverlay.h>
#import <MapKit/MKTileOverlayRenderer.h>
#import <MapKit/MKTypes.h>
#import <MapKit/MKMapCamera.h>

#if TARGET_OS_IPHONE
#import <MapKit/MKReverseGeocoder.h>
#import <MapKit/MKOverlayView.h>
#import <MapKit/MKOverlayPathView.h>
#import <MapKit/MKPolygonView.h>
#import <MapKit/MKPolylineView.h>
#import <MapKit/MKCircleView.h>
#import <MapKit/MKUserTrackingBarButtonItem.h>
#endif

#endif
// ==========  MapKit.framework/Headers/MKPolygonView.h
//
//  MKPolygonView.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKPolygon.h>
#import <MapKit/MKOverlayPathView.h>
#import <MapKit/MKFoundation.h>

// Prefer MKPolygonRenderer
MK_CLASS_AVAILABLE(NA, 4_0) __WATCHOS_PROHIBITED
@interface MKPolygonView : MKOverlayPathView

- (instancetype)initWithPolygon:(MKPolygon *)polygon NS_DEPRECATED_IOS(4_0, 7_0);
@property (nonatomic, readonly) MKPolygon *polygon NS_DEPRECATED_IOS(4_0, 7_0);

@end
// ==========  MapKit.framework/Headers/MKOverlayRenderer.h
//
//  MKOverlayRenderer.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>
#import <MapKit/MKOverlay.h>

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 7_0) __WATCHOS_PROHIBITED
@interface MKOverlayRenderer : NSObject

- (instancetype)initWithOverlay:(id <MKOverlay>)overlay NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly) id <MKOverlay> overlay;

// Convert points relative to this view to absolute MKMapPoints
- (CGPoint)pointForMapPoint:(MKMapPoint)mapPoint;
- (MKMapPoint)mapPointForPoint:(CGPoint)point;

- (CGRect)rectForMapRect:(MKMapRect)mapRect;
- (MKMapRect)mapRectForRect:(CGRect)rect;

// Return YES if the renderer is currently ready to draw in the specified rect.
// Return NO if the renderer will not draw in the specified rect or if the
// data necessary to draw in the specified rect is not available.  In the 
// case where the renderer may want to draw in the specified rect but the data is
// not available, use setNeedsDisplayInMapRect:zoomLevel: to signal when the
// data does become available.
- (BOOL)canDrawMapRect:(MKMapRect)mapRect
             zoomScale:(MKZoomScale)zoomScale;

- (void)drawMapRect:(MKMapRect)mapRect
          zoomScale:(MKZoomScale)zoomScale
          inContext:(CGContextRef)context;

- (void)setNeedsDisplay;

- (void)setNeedsDisplayInMapRect:(MKMapRect)mapRect;     

- (void)setNeedsDisplayInMapRect:(MKMapRect)mapRect
                       zoomScale:(MKZoomScale)zoomScale;

@property CGFloat alpha;

@property (readonly) CGFloat contentScaleFactor;

@end

// Road widths are typically not drawn to scale on the map.  This function
// returns the approximate width in points of roads at the specified zoomScale.
// The result of this function is suitable for use with CGContextSetLineWidth.
MK_EXTERN CGFloat MKRoadWidthAtZoomScale(MKZoomScale zoomScale) NS_AVAILABLE(10_9, 4_0) __WATCHOS_PROHIBITED;

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKDirectionsResponse.h
//
//  MKDirectionsResponse.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKDirectionsTypes.h>
#import <CoreLocation/CoreLocation.h>

@class MKMapItem;
@class MKPolyline;
@class MKRoute;
@class MKRouteStep;

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 7_0) __WATCHOS_PROHIBITED
@interface MKDirectionsResponse : NSObject

// Source and destination may be filled with additional details compared to the request object.
@property (nonatomic, readonly) MKMapItem *source;
@property (nonatomic, readonly) MKMapItem *destination;

@property (nonatomic, readonly) NSArray<MKRoute *> *routes;

@end

MK_CLASS_AVAILABLE(10_9, 7_0) __WATCHOS_PROHIBITED
@interface MKRoute : NSObject

@property (nonatomic, readonly) NSString *name; // localized description of the route's significant feature, e.g. "US-101"

@property (nonatomic, readonly) NSArray<NSString *> *advisoryNotices; // localized notices of route conditions. e.g. "Avoid during winter storms"

@property (nonatomic, readonly) CLLocationDistance distance; // overall route distance in meters
@property (nonatomic, readonly) NSTimeInterval expectedTravelTime;

@property (nonatomic, readonly) MKDirectionsTransportType transportType; // overall route transport type

@property (nonatomic, readonly) MKPolyline *polyline; // detailed route geometry

@property (nonatomic, readonly) NSArray<MKRouteStep *> *steps;

@end

MK_CLASS_AVAILABLE(10_9, 7_0) __WATCHOS_PROHIBITED
@interface MKRouteStep : NSObject

@property (nonatomic, readonly) NSString *instructions; // localized written instructions
@property (nonatomic, readonly, nullable) NSString *notice; // additional localized legal or warning notice related to this step (e.g. "Do not cross tracks when lights flash")

@property (nonatomic, readonly) MKPolyline *polyline; // detailed step geometry

@property (nonatomic, readonly) CLLocationDistance distance; // step distance in meters

@property (nonatomic, readonly) MKDirectionsTransportType transportType; // step transport type (may differ from overall route transport type)

@end

MK_CLASS_AVAILABLE(10_9, 7_0) __WATCHOS_PROHIBITED
@interface MKETAResponse : NSObject

// Source and destination may be filled with additional details compared to the request object.
@property (nonatomic, readonly) MKMapItem *source;
@property (nonatomic, readonly) MKMapItem *destination;
@property (nonatomic, readonly) NSTimeInterval expectedTravelTime;
@property (nonatomic, readonly) CLLocationDistance distance NS_AVAILABLE(10_11, 9_0); // overall route distance in meters
@property (nonatomic, readonly) NSDate *expectedArrivalDate NS_AVAILABLE(10_11, 9_0);
@property (nonatomic, readonly) NSDate *expectedDepartureDate NS_AVAILABLE(10_11, 9_0);
@property (nonatomic, readonly) MKDirectionsTransportType transportType NS_AVAILABLE(10_11, 9_0);
@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKTileOverlayRenderer.h
//
//  MKTileOverlayRenderer.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKOverlayRenderer.h>
#import <MapKit/MKTileOverlay.h>

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 7_0) __WATCHOS_PROHIBITED
@interface MKTileOverlayRenderer : MKOverlayRenderer

- (instancetype)initWithTileOverlay:(MKTileOverlay *)overlay;

- (void)reloadData;

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKUserLocation.h
//
//  MKUserLocation.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKAnnotation.h>

@class CLLocation;
@class MKUserLocationInternal;

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 3_0) __WATCHOS_PROHIBITED
@interface MKUserLocation : NSObject <MKAnnotation>

// Returns YES if the user's location is being updated.
@property (readonly, nonatomic, getter=isUpdating) BOOL updating;

// Returns nil if the owning MKMapView's showsUserLocation is NO or the user's location has yet to be determined.
@property (readonly, nonatomic, nullable) CLLocation *location;

// Returns nil if not in MKUserTrackingModeFollowWithHeading
@property (readonly, nonatomic, nullable) CLHeading *heading NS_AVAILABLE(10_9, 5_0);

// The title to be displayed for the user location annotation.
@property (nonatomic, copy, nullable) NSString *title;

// The subtitle to be displayed for the user location annotation.
@property (nonatomic, copy, nullable) NSString *subtitle;

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKLocalSearchResponse.h
//
//  MKLocalSearchResponse.h
//  MapKit
//
//  Copyright (c) 2012-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>

@class MKMapItem;

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 6_1) __WATCHOS_PROHIBITED
@interface MKLocalSearchResponse : NSObject

// An array of MKMapItems sorted by relevance in descending order
@property (nonatomic, readonly) NSArray<MKMapItem *> *mapItems;

@property (nonatomic, readonly) MKCoordinateRegion boundingRegion;

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKTypes.h
//
//  MKTypes.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, MKMapType) {
    MKMapTypeStandard = 0,
    MKMapTypeSatellite,
    MKMapTypeHybrid,
    MKMapTypeSatelliteFlyover NS_ENUM_AVAILABLE(10_11, 9_0),
    MKMapTypeHybridFlyover NS_ENUM_AVAILABLE(10_11, 9_0),
} NS_ENUM_AVAILABLE(10_9, 3_0) __WATCHOS_PROHIBITED;

MK_EXTERN NSString *MKErrorDomain;

typedef NS_ENUM(NSUInteger, MKErrorCode) {
    MKErrorUnknown = 1,
    MKErrorServerFailure,
    MKErrorLoadingThrottled,
    MKErrorPlacemarkNotFound,
    MKErrorDirectionsNotFound NS_ENUM_AVAILABLE(10_9, 7_0)
} NS_ENUM_AVAILABLE(10_9, 3_0) __WATCHOS_PROHIBITED;

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKGeometry.h
//
//  MKGeometry.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <CoreLocation/CoreLocation.h>
#import <MapKit/MKFoundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef struct {
    CLLocationDegrees latitudeDelta;
    CLLocationDegrees longitudeDelta;
} MKCoordinateSpan;

typedef struct {
	CLLocationCoordinate2D center;
	MKCoordinateSpan span;
} MKCoordinateRegion;


NS_INLINE MKCoordinateSpan MKCoordinateSpanMake(CLLocationDegrees latitudeDelta, CLLocationDegrees longitudeDelta)
{
    MKCoordinateSpan span;
    span.latitudeDelta = latitudeDelta;
    span.longitudeDelta = longitudeDelta;
    return span;
}

NS_INLINE MKCoordinateRegion MKCoordinateRegionMake(CLLocationCoordinate2D centerCoordinate, MKCoordinateSpan span)
{
	MKCoordinateRegion region;
	region.center = centerCoordinate;
    region.span = span;
	return region;
}

MK_EXTERN MKCoordinateRegion MKCoordinateRegionMakeWithDistance(CLLocationCoordinate2D centerCoordinate, CLLocationDistance latitudinalMeters, CLLocationDistance longitudinalMeters);

// Projected geometry is available in iPhone OS 4.0 or later and Mac OS X 10.9 or later
#if (__IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED || __MAC_10_9 <= __MAC_OS_X_VERSION_MAX_ALLOWED)

// An MKMapPoint is a coordinate that has been projected for use on the
// two-dimensional map.  An MKMapPoint always refers to a place in the world
// and can be converted to a CLLocationCoordinate2D and back.
typedef struct {
    double x;
    double y;
} MKMapPoint;

typedef struct {
    double width;
    double height;
} MKMapSize;

typedef struct {
    MKMapPoint origin;
    MKMapSize size;
} MKMapRect;

// MKZoomScale provides a conversion factor between MKMapPoints and screen points.
// When MKZoomScale = 1, 1 screen point = 1 MKMapPoint.  When MKZoomScale is
// 0.5, 1 screen point = 2 MKMapPoints.
typedef CGFloat MKZoomScale;
#endif

MK_EXTERN const MKMapSize MKMapSizeWorld NS_AVAILABLE(10_9, 4_0);
// The rect that contains every map point in the world.
MK_EXTERN const MKMapRect MKMapRectWorld NS_AVAILABLE(10_9, 4_0);

// Conversion between unprojected and projected coordinates
MK_EXTERN MKMapPoint MKMapPointForCoordinate(CLLocationCoordinate2D coordinate) NS_AVAILABLE(10_9, 4_0);
MK_EXTERN CLLocationCoordinate2D MKCoordinateForMapPoint(MKMapPoint mapPoint) NS_AVAILABLE(10_9, 4_0);

// Conversion between distances and projected coordinates
MK_EXTERN CLLocationDistance MKMetersPerMapPointAtLatitude(CLLocationDegrees latitude) NS_AVAILABLE(10_9, 4_0);
MK_EXTERN double MKMapPointsPerMeterAtLatitude(CLLocationDegrees latitude) NS_AVAILABLE(10_9, 4_0);

MK_EXTERN CLLocationDistance MKMetersBetweenMapPoints(MKMapPoint a, MKMapPoint b) NS_AVAILABLE(10_9, 4_0);

MK_EXTERN const MKMapRect MKMapRectNull NS_AVAILABLE(10_9, 4_0);

#if (__IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED || __MAC_10_9 <= __MAC_OS_X_VERSION_MAX_ALLOWED)

// Geometric operations on MKMapPoint/Size/Rect.  See CGGeometry.h for 
// information on the CGFloat versions of these functions.
NS_INLINE MKMapPoint MKMapPointMake(double x, double y) {
    return (MKMapPoint){x, y};
}
NS_INLINE MKMapSize MKMapSizeMake(double width, double height) {
    return (MKMapSize){width, height};
}
NS_INLINE MKMapRect MKMapRectMake(double x, double y, double width, double height) {
    return (MKMapRect){ MKMapPointMake(x, y), MKMapSizeMake(width, height) };
}
NS_INLINE double MKMapRectGetMinX(MKMapRect rect) {
    return rect.origin.x;
}
NS_INLINE double MKMapRectGetMinY(MKMapRect rect) {
    return rect.origin.y;
}
NS_INLINE double MKMapRectGetMidX(MKMapRect rect) {
    return rect.origin.x + rect.size.width / 2.0;
}
NS_INLINE double MKMapRectGetMidY(MKMapRect rect) {
    return rect.origin.y + rect.size.height / 2.0;
}
NS_INLINE double MKMapRectGetMaxX(MKMapRect rect) {
    return rect.origin.x + rect.size.width;
}
NS_INLINE double MKMapRectGetMaxY(MKMapRect rect) {
    return rect.origin.y + rect.size.height;
}
NS_INLINE double MKMapRectGetWidth(MKMapRect rect) {
    return rect.size.width;
}
NS_INLINE double MKMapRectGetHeight(MKMapRect rect) {
    return rect.size.height;
}
NS_INLINE BOOL MKMapPointEqualToPoint(MKMapPoint point1, MKMapPoint point2) {
    return point1.x == point2.x && point1.y == point2.y;
}
NS_INLINE BOOL MKMapSizeEqualToSize(MKMapSize size1, MKMapSize size2) {
    return size1.width == size2.width && size1.height == size2.height;
}
NS_INLINE BOOL MKMapRectEqualToRect(MKMapRect rect1, MKMapRect rect2) {
    return 
    MKMapPointEqualToPoint(rect1.origin, rect2.origin) &&
    MKMapSizeEqualToSize(rect1.size, rect2.size);
}

NS_INLINE BOOL MKMapRectIsNull(MKMapRect rect) {
    return MKMapPointEqualToPoint(rect.origin, MKMapRectNull.origin);
}

NS_INLINE BOOL MKMapRectIsEmpty(MKMapRect rect) {
    return MKMapRectIsNull(rect) || (rect.size.width == 0.0 && rect.size.height == 0.0);
}

NS_INLINE NSString *MKStringFromMapPoint(MKMapPoint point) {
    return [NSString stringWithFormat:@"{%.1f, %.1f}", point.x, point.y];
}

NS_INLINE NSString *MKStringFromMapSize(MKMapSize size) {
    return [NSString stringWithFormat:@"{%.1f, %.1f}", size.width, size.height];
}

NS_INLINE NSString *MKStringFromMapRect(MKMapRect rect) {
    return [NSString stringWithFormat:@"{%@, %@}", MKStringFromMapPoint(rect.origin), MKStringFromMapSize(rect.size)];
}
#endif

MK_EXTERN MKMapRect MKMapRectUnion(MKMapRect rect1, MKMapRect rect2) NS_AVAILABLE(10_9, 4_0);
MK_EXTERN MKMapRect MKMapRectIntersection(MKMapRect rect1, MKMapRect rect2) NS_AVAILABLE(10_9, 4_0);
MK_EXTERN MKMapRect MKMapRectInset(MKMapRect rect, double dx, double dy) NS_AVAILABLE(10_9, 4_0);
MK_EXTERN MKMapRect MKMapRectOffset(MKMapRect rect, double dx, double dy) NS_AVAILABLE(10_9, 4_0);
MK_EXTERN void MKMapRectDivide(MKMapRect rect, MKMapRect *slice, MKMapRect *remainder, double amount, CGRectEdge edge) NS_AVAILABLE(10_9, 4_0);

MK_EXTERN BOOL MKMapRectContainsPoint(MKMapRect rect, MKMapPoint point) NS_AVAILABLE(10_9, 4_0);
MK_EXTERN BOOL MKMapRectContainsRect(MKMapRect rect1, MKMapRect rect2) NS_AVAILABLE(10_9, 4_0);
MK_EXTERN BOOL MKMapRectIntersectsRect(MKMapRect rect1, MKMapRect rect2) NS_AVAILABLE(10_9, 4_0);

MK_EXTERN MKCoordinateRegion MKCoordinateRegionForMapRect(MKMapRect rect) NS_AVAILABLE(10_9, 4_0);

MK_EXTERN BOOL MKMapRectSpans180thMeridian(MKMapRect rect) NS_AVAILABLE(10_9, 4_0);
// For map rects that span the 180th meridian, this returns the portion of the rect
// that lies outside of the world rect wrapped around to the other side of the
// world.  The portion of the rect that lies inside the world rect can be 
// determined with MKMapRectIntersection(rect, MKMapRectWorld).
MK_EXTERN MKMapRect MKMapRectRemainder(MKMapRect rect) NS_AVAILABLE(10_9, 4_0);


@interface NSValue (NSValueMapKitGeometryExtensions)

+ (NSValue *)valueWithMKCoordinate:(CLLocationCoordinate2D)coordinate;
+ (NSValue *)valueWithMKCoordinateSpan:(MKCoordinateSpan)span;

@property (readonly) CLLocationCoordinate2D MKCoordinateValue;
@property (readonly) MKCoordinateSpan MKCoordinateSpanValue;

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKUserTrackingBarButtonItem.h
//
//  MKUserTrackingBarButtonItem.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <UIKit/UIBarButtonItem.h>
#import <MapKit/MKFoundation.h>

@class MKMapView;

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(NA, 5_0) __WATCHOS_PROHIBITED
@interface MKUserTrackingBarButtonItem : UIBarButtonItem

- (instancetype)initWithMapView:(nullable MKMapView *)mapView NS_DESIGNATED_INITIALIZER;
@property (nonatomic, strong, nullable) MKMapView *mapView;

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKTileOverlay.h
//
//  MKTileOverlay.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKOverlay.h>

NS_ASSUME_NONNULL_BEGIN

// MKTileOverlay represents a data source for raster image tiles in the spherical mercator projection (EPSG:3857).
MK_CLASS_AVAILABLE(10_9, 7_0) __WATCHOS_PROHIBITED
@interface MKTileOverlay : NSObject <MKOverlay>

- (instancetype)initWithURLTemplate:(nullable NSString *)URLTemplate NS_DESIGNATED_INITIALIZER; // URL template is a string where the substrings "{x}", "{y}", "{z}", and "{scale}" are replaced with values from a tile path to create a URL to load. For example: http://server/path?x={x}&y={y}&z={z}&scale={scale}.

@property CGSize tileSize; // default is 256x256

@property (getter=isGeometryFlipped) BOOL geometryFlipped; // Default is NO. If NO, a tile at x=0, y=0 is the upper left, otherwise it is in the lower left.

// The minimum/maximum zoom level at which tile data is available for this overlay. A tile at level 0 covers the entire world, at level 1 it covers 1/4th of the world, at level 2 it covers 1/16th of the world, and so on.
@property NSInteger minimumZ;
@property NSInteger maximumZ;

@property (readonly, nullable) NSString *URLTemplate;

@property (nonatomic) BOOL canReplaceMapContent;

@end

typedef struct {
    NSInteger x;
    NSInteger y;
    NSInteger z;
    CGFloat contentScaleFactor; // The screen scale that the tile will be shown on. Either 1.0 or 2.0.
} MKTileOverlayPath;

// Subclassers may override these methods to customize the loading behavior of MKTileOverlay
@interface MKTileOverlay (CustomLoading)

- (NSURL *)URLForTilePath:(MKTileOverlayPath)path; // default implementation fills out the URLTemplate

// Load the requested tile and call the callback block with the tile data or with an error if the tile could not be loaded. The default implementation first uses -URLForTilePath to get a URL and then it loads it asynchronously.
- (void)loadTileAtPath:(MKTileOverlayPath)path result:(void (^)(NSData * __nullable tileData, NSError * __nullable error))result;

@end

NS_ASSUME_NONNULL_END

// ==========  MapKit.framework/Headers/MKDirectionsRequest.h
//
//  MKDirectionsRequest.h
//  MapKit
//
//  Copyright (c) 2012-2014, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MKMapItem.h>
#import <MapKit/MKDirectionsTypes.h>

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 6_0) __WATCHOS_PROHIBITED
@interface MKDirectionsRequest : NSObject

@property (nonatomic, strong, nullable) MKMapItem *source;
- (void)setSource:(nullable MKMapItem *)source NS_AVAILABLE(10_9, 7_0);

@property (nonatomic, strong, nullable) MKMapItem *destination;
- (void)setDestination:(nullable MKMapItem *)destination NS_AVAILABLE(10_9, 7_0);

@end

@interface MKDirectionsRequest (MKRequestOptions)

@property (nonatomic) MKDirectionsTransportType transportType NS_AVAILABLE(10_9, 7_0); // Default is MKDirectionsTransportTypeAny

@property (nonatomic) BOOL requestsAlternateRoutes NS_AVAILABLE(10_9, 7_0); // if YES and there is more than one reasonable way to route from source to destination, allow the route server to return multiple routes. Default is NO.

// Set either departure or arrival date to hint to the route server when the trip will take place.
@property (nonatomic, copy, nullable) NSDate *departureDate NS_AVAILABLE(10_9, 7_0);
@property (nonatomic, copy, nullable) NSDate *arrivalDate NS_AVAILABLE(10_9, 7_0);

@end

@interface MKDirectionsRequest (MKDirectionsURL)

- (instancetype)initWithContentsOfURL:(NSURL *)url NS_AVAILABLE(10_9, 6_0);
+ (BOOL)isDirectionsRequestURL:(NSURL *)url NS_AVAILABLE(10_9, 6_0);

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKFoundation.h
//
//  MKFoundation.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Availability.h>

#ifdef __cplusplus
#define MK_EXTERN       extern "C" __attribute__((visibility ("default")))
#else
#define MK_EXTERN       extern __attribute__((visibility ("default")))
#endif

#define MK_CLASS_AVAILABLE(_macIntro, _iphoneIntro) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE(_macIntro, _iphoneIntro)
#define MK_CLASS_DEPRECATED(_macIntro, _macDep, _iphoneIntro, _iphoneDep) __attribute__((visibility("default"))) NS_DEPRECATED(_macIntro, macDep, _iphoneIntro,_iphoneDep)
// ==========  MapKit.framework/Headers/MKLocalSearchRequest.h
//
//  MKLocalSearchRequest.h
//  MapKit
//
//  Copyright (c) 2012-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 6_1) __WATCHOS_PROHIBITED
@interface MKLocalSearchRequest : NSObject <NSCopying>

@property (nonatomic, copy, nullable) NSString *naturalLanguageQuery;
@property (nonatomic, assign) MKCoordinateRegion region;

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKMapItem.h
//
//  MKMapItem.h
//  MapKit
//
//  Copyright 2011-2012, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKPlacemark.h>

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 6_0)
@interface MKMapItem : NSObject

// If this MKMapItem represents your current location (isCurrentLocation == YES), then placemark will be nil.
@property (nonatomic, readonly) MKPlacemark *placemark;
@property (nonatomic, readonly) BOOL isCurrentLocation;

@property (nonatomic, copy, nullable) NSString *name;
@property (nonatomic, copy, nullable) NSString *phoneNumber;

@property (nonatomic, strong, nullable) NSURL *url;

@property (nonatomic, copy, nullable) NSTimeZone *timeZone NS_AVAILABLE(10_11, 9_0);

+ (MKMapItem *)mapItemForCurrentLocation;
- (instancetype)initWithPlacemark:(MKPlacemark *)placemark;

- (BOOL)openInMapsWithLaunchOptions:(nullable NSDictionary<NSString *, id> *)launchOptions;
+ (BOOL)openMapsWithItems:(NSArray<MKMapItem *> *)mapItems launchOptions:(nullable NSDictionary<NSString *, id> *)launchOptions;

@end

MK_EXTERN NSString * const MKLaunchOptionsDirectionsModeKey     NS_AVAILABLE(10_9, 6_0); // Key to a directions mode
MK_EXTERN NSString * const MKLaunchOptionsMapTypeKey            NS_AVAILABLE(10_9, 6_0) __WATCHOS_PROHIBITED; // Key to an NSNumber corresponding to a MKMapType
MK_EXTERN NSString * const MKLaunchOptionsShowsTrafficKey       NS_AVAILABLE(10_9, 6_0) __WATCHOS_PROHIBITED; // Key to a boolean NSNumber

// Directions modes
MK_EXTERN NSString * const MKLaunchOptionsDirectionsModeDriving NS_AVAILABLE(10_9, 6_0);
MK_EXTERN NSString * const MKLaunchOptionsDirectionsModeWalking NS_AVAILABLE(10_9, 6_0);
MK_EXTERN NSString * const MKLaunchOptionsDirectionsModeTransit NS_AVAILABLE(10_11, 9_0);

// If center and span are present, having a camera as well is undefined
MK_EXTERN NSString * const MKLaunchOptionsMapCenterKey          NS_AVAILABLE(10_9, 6_0); // Key to an NSValue-encoded CLLocationCoordinate2D
MK_EXTERN NSString * const MKLaunchOptionsMapSpanKey            NS_AVAILABLE(10_9, 6_0); // Key to an NSValue-encoded MKCoordinateSpan

MK_EXTERN NSString * const MKLaunchOptionsCameraKey             NS_AVAILABLE(10_10, 7_1); // Key to MKMapCamera object

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKMapView.h
//
//  MKMapView.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKAnnotationView.h>
#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>
#import <MapKit/MKTypes.h>
#import <MapKit/MKOverlay.h>
#import <MapKit/MKOverlayRenderer.h>
#if TARGET_OS_IPHONE
#import <MapKit/MKOverlayView.h>
#endif

@class MKUserLocation;
@class MKMapCamera;

@protocol MKMapViewDelegate;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, MKUserTrackingMode) {
	MKUserTrackingModeNone = 0, // the user's location is not followed
	MKUserTrackingModeFollow, // the map follows the user's location
	MKUserTrackingModeFollowWithHeading, // the map follows the user's location and heading
} NS_ENUM_AVAILABLE(NA, 5_0) __WATCHOS_PROHIBITED;

#if TARGET_OS_IPHONE
MK_CLASS_AVAILABLE(NA, 3_0) __WATCHOS_PROHIBITED
@interface MKMapView : UIView <NSCoding>
#else
MK_CLASS_AVAILABLE(10_9, NA)
@interface MKMapView : NSView <NSCoding>
#endif

@property (nonatomic, weak, nullable) id <MKMapViewDelegate> delegate;

// Changing the map type or region can cause the map to start loading map content.
// The loading delegate methods will be called as map content is loaded.
@property (nonatomic) MKMapType mapType;

// Region is the coordinate and span of the map.
// Region may be modified to fit the aspect ratio of the view using regionThatFits:.
@property (nonatomic) MKCoordinateRegion region;
- (void)setRegion:(MKCoordinateRegion)region animated:(BOOL)animated;

// centerCoordinate allows the coordinate of the region to be changed without changing the zoom level.
@property (nonatomic) CLLocationCoordinate2D centerCoordinate;
- (void)setCenterCoordinate:(CLLocationCoordinate2D)coordinate animated:(BOOL)animated;

// Returns a region of the aspect ratio of the map view that contains the given region, with the same center point.
- (MKCoordinateRegion)regionThatFits:(MKCoordinateRegion)region;

// Access the visible region of the map in projected coordinates.
@property (nonatomic) MKMapRect visibleMapRect;
- (void)setVisibleMapRect:(MKMapRect)mapRect animated:(BOOL)animate;

// Returns an MKMapRect modified to fit the aspect ratio of the map.
- (MKMapRect)mapRectThatFits:(MKMapRect)mapRect;

// To be used in testing only
- (void)_handleSelectionAtPoint:(CGPoint)locationInView;

// Edge padding is the minumum padding on each side around the specified MKMapRect.
#if TARGET_OS_IPHONE
- (void)setVisibleMapRect:(MKMapRect)mapRect edgePadding:(UIEdgeInsets)insets animated:(BOOL)animate;
- (MKMapRect)mapRectThatFits:(MKMapRect)mapRect edgePadding:(UIEdgeInsets)insets;
#else
- (void)setVisibleMapRect:(MKMapRect)mapRect edgePadding:(NSEdgeInsets)insets animated:(BOOL)animate;
- (MKMapRect)mapRectThatFits:(MKMapRect)mapRect edgePadding:(NSEdgeInsets)insets;
#endif

@property (nonatomic, copy) MKMapCamera *camera NS_AVAILABLE(10_9, 7_0);
- (void)setCamera:(MKMapCamera *)camera animated:(BOOL)animated NS_AVAILABLE(10_9, 7_0);

#if TARGET_OS_IPHONE
- (CGPoint)convertCoordinate:(CLLocationCoordinate2D)coordinate toPointToView:(nullable UIView *)view;
- (CLLocationCoordinate2D)convertPoint:(CGPoint)point toCoordinateFromView:(nullable UIView *)view;
- (CGRect)convertRegion:(MKCoordinateRegion)region toRectToView:(nullable UIView *)view;
- (MKCoordinateRegion)convertRect:(CGRect)rect toRegionFromView:(nullable UIView *)view;
#else
- (CGPoint)convertCoordinate:(CLLocationCoordinate2D)coordinate toPointToView:(nullable NSView *)view;
- (CLLocationCoordinate2D)convertPoint:(CGPoint)point toCoordinateFromView:(nullable NSView *)view;
- (CGRect)convertRegion:(MKCoordinateRegion)region toRectToView:(nullable NSView *)view;
- (MKCoordinateRegion)convertRect:(CGRect)rect toRegionFromView:(nullable NSView *)view;
#endif

// Control the types of user interaction available
// Zoom and scroll are enabled by default.
@property (nonatomic, getter=isZoomEnabled) BOOL zoomEnabled;
@property (nonatomic, getter=isScrollEnabled) BOOL scrollEnabled;
// Rotate and pitch are enabled by default on Mac OS X and on iOS 7.0 and later.
@property (nonatomic, getter=isRotateEnabled) BOOL rotateEnabled NS_AVAILABLE(10_9, 7_0);
@property (nonatomic, getter=isPitchEnabled) BOOL pitchEnabled NS_AVAILABLE(10_9, 7_0);

#if !TARGET_OS_IPHONE
@property (nonatomic) BOOL showsZoomControls NS_AVAILABLE(10_9, NA);
#endif


@property (nonatomic) BOOL showsCompass NS_AVAILABLE(10_9, 9_0);
@property (nonatomic) BOOL showsScale NS_AVAILABLE(10_10, 9_0);

@property (nonatomic) BOOL showsPointsOfInterest NS_AVAILABLE(10_9, 7_0); // Affects MKMapTypeStandard and MKMapTypeHybrid
@property (nonatomic) BOOL showsBuildings NS_AVAILABLE(10_9, 7_0); // Affects MKMapTypeStandard
@property (nonatomic) BOOL showsTraffic NS_AVAILABLE(10_11, 9_0); // Affects MKMapTypeStandard and MKMapTypeHybrid

// Set to YES to add the user location annotation to the map and start updating its location
@property (nonatomic) BOOL showsUserLocation;

// The annotation representing the user's location
@property (nonatomic, readonly) MKUserLocation *userLocation;

#if TARGET_OS_IPHONE
@property (nonatomic) MKUserTrackingMode userTrackingMode NS_AVAILABLE(NA, 5_0);
- (void)setUserTrackingMode:(MKUserTrackingMode)mode animated:(BOOL)animated NS_AVAILABLE(NA, 5_0);
#endif

// Returns YES if the user's location is displayed within the currently visible map region.
@property (nonatomic, readonly, getter=isUserLocationVisible) BOOL userLocationVisible;

// Annotations are models used to annotate coordinates on the map. 
// Implement mapView:viewForAnnotation: on MKMapViewDelegate to return the annotation view for each annotation.
- (void)addAnnotation:(id <MKAnnotation>)annotation;
- (void)addAnnotations:(NSArray<id<MKAnnotation>> *)annotations;

- (void)removeAnnotation:(id <MKAnnotation>)annotation;
- (void)removeAnnotations:(NSArray<id<MKAnnotation>> *)annotations;

@property (nonatomic, readonly) NSArray<id<MKAnnotation>> *annotations;
- (NSSet<id<MKAnnotation>> *)annotationsInMapRect:(MKMapRect)mapRect NS_AVAILABLE(10_9, 4_2);

// Currently displayed view for an annotation; returns nil if the view for the annotation isn't being displayed.
- (nullable MKAnnotationView *)viewForAnnotation:(id <MKAnnotation>)annotation;

// Used by the delegate to acquire an already allocated annotation view, in lieu of allocating a new one.
- (nullable MKAnnotationView *)dequeueReusableAnnotationViewWithIdentifier:(NSString *)identifier;

// Select or deselect a given annotation.  Asks the delegate for the corresponding annotation view if necessary.
- (void)selectAnnotation:(id <MKAnnotation>)annotation animated:(BOOL)animated;
- (void)deselectAnnotation:(nullable id <MKAnnotation>)annotation animated:(BOOL)animated;
@property (nonatomic, copy) NSArray<id<MKAnnotation>> *selectedAnnotations;

// annotationVisibleRect is the visible rect where the annotations views are currently displayed.
// The delegate can use annotationVisibleRect when animating the adding of the annotations views in mapView:didAddAnnotationViews:
@property (nonatomic, readonly) CGRect annotationVisibleRect;

// Position the map such that the provided array of annotations are all visible to the fullest extent possible.
- (void)showAnnotations:(NSArray<id<MKAnnotation>> *)annotations animated:(BOOL)animated NS_AVAILABLE(10_9, 7_0);

@end

typedef NS_ENUM(NSInteger, MKOverlayLevel) {
    MKOverlayLevelAboveRoads = 0, // note that labels include shields and point of interest icons.
    MKOverlayLevelAboveLabels
} NS_ENUM_AVAILABLE(10_9, 7_0) __WATCHOS_PROHIBITED;

@interface MKMapView (OverlaysAPI)

// Overlays are models used to represent areas to be drawn on top of the map.
// This is in contrast to annotations, which represent points on the map.
// Implement -mapView:rendererForOverlay: on MKMapViewDelegate to return the renderer for each overlay.
- (void)addOverlay:(id <MKOverlay>)overlay level:(MKOverlayLevel)level NS_AVAILABLE(10_9, 7_0);
- (void)addOverlays:(NSArray<id<MKOverlay>> *)overlays level:(MKOverlayLevel)level NS_AVAILABLE(10_9, 7_0);

- (void)removeOverlay:(id <MKOverlay>)overlay NS_AVAILABLE(10_9, 4_0);
- (void)removeOverlays:(NSArray<id<MKOverlay>> *)overlays NS_AVAILABLE(10_9, 4_0);

- (void)insertOverlay:(id <MKOverlay>)overlay atIndex:(NSUInteger)index level:(MKOverlayLevel)level NS_AVAILABLE(10_9, 7_0);

- (void)insertOverlay:(id <MKOverlay>)overlay aboveOverlay:(id <MKOverlay>)sibling NS_AVAILABLE(10_9, 4_0);
- (void)insertOverlay:(id <MKOverlay>)overlay belowOverlay:(id <MKOverlay>)sibling NS_AVAILABLE(10_9, 4_0);

- (void)exchangeOverlay:(id <MKOverlay>)overlay1 withOverlay:(id <MKOverlay>)overlay2 NS_AVAILABLE(10_9, 7_0);

@property (nonatomic, readonly) NSArray<id<MKOverlay>> *overlays NS_AVAILABLE(10_9, 4_0);
- (NSArray<id<MKOverlay>> *)overlaysInLevel:(MKOverlayLevel)level NS_AVAILABLE(10_9, 7_0);

// Current renderer for overlay; returns nil if the overlay is not shown.
- (nullable MKOverlayRenderer *)rendererForOverlay:(id <MKOverlay>)overlay NS_AVAILABLE(10_9, 7_0);

#if TARGET_OS_IPHONE
// Currently displayed view for overlay; returns nil if the view has not been created yet.
// Prefer using MKOverlayRenderer and -rendererForOverlay.
- (MKOverlayView *)viewForOverlay:(id <MKOverlay>)overlay NS_DEPRECATED_IOS(4_0, 7_0);
#endif

// These methods operate implicitly on overlays in MKOverlayLevelAboveLabels and may be deprecated in a future release in favor of the methods that specify the level.
- (void)addOverlay:(id <MKOverlay>)overlay NS_AVAILABLE(10_9, 4_0);
- (void)addOverlays:(NSArray<id<MKOverlay>> *)overlays NS_AVAILABLE(10_9, 4_0);

- (void)insertOverlay:(id <MKOverlay>)overlay atIndex:(NSUInteger)index NS_AVAILABLE(10_9, 4_0);
- (void)exchangeOverlayAtIndex:(NSUInteger)index1 withOverlayAtIndex:(NSUInteger)index2 NS_AVAILABLE(10_9, 4_0);

@end

__WATCHOS_PROHIBITED
@protocol MKMapViewDelegate <NSObject>
@optional

- (void)mapView:(MKMapView *)mapView regionWillChangeAnimated:(BOOL)animated;
- (void)mapView:(MKMapView *)mapView regionDidChangeAnimated:(BOOL)animated;

- (void)mapViewWillStartLoadingMap:(MKMapView *)mapView;
- (void)mapViewDidFinishLoadingMap:(MKMapView *)mapView;
- (void)mapViewDidFailLoadingMap:(MKMapView *)mapView withError:(NSError *)error;

- (void)mapViewWillStartRenderingMap:(MKMapView *)mapView NS_AVAILABLE(10_9, 7_0);
- (void)mapViewDidFinishRenderingMap:(MKMapView *)mapView fullyRendered:(BOOL)fullyRendered NS_AVAILABLE(10_9, 7_0);

// mapView:viewForAnnotation: provides the view for each annotation.
// This method may be called for all or some of the added annotations.
// For MapKit provided annotations (eg. MKUserLocation) return nil to use the MapKit provided annotation view.
- (nullable MKAnnotationView *)mapView:(MKMapView *)mapView viewForAnnotation:(id <MKAnnotation>)annotation;

// mapView:didAddAnnotationViews: is called after the annotation views have been added and positioned in the map.
// The delegate can implement this method to animate the adding of the annotations views.
// Use the current positions of the annotation views as the destinations of the animation.
- (void)mapView:(MKMapView *)mapView didAddAnnotationViews:(NSArray<MKAnnotationView *> *)views;

#if TARGET_OS_IPHONE
// mapView:annotationView:calloutAccessoryControlTapped: is called when the user taps on left & right callout accessory UIControls.
- (void)mapView:(MKMapView *)mapView annotationView:(MKAnnotationView *)view calloutAccessoryControlTapped:(UIControl *)control;
#endif

- (void)mapView:(MKMapView *)mapView didSelectAnnotationView:(MKAnnotationView *)view NS_AVAILABLE(10_9, 4_0);
- (void)mapView:(MKMapView *)mapView didDeselectAnnotationView:(MKAnnotationView *)view NS_AVAILABLE(10_9, 4_0);

- (void)mapViewWillStartLocatingUser:(MKMapView *)mapView NS_AVAILABLE(10_9, 4_0);
- (void)mapViewDidStopLocatingUser:(MKMapView *)mapView NS_AVAILABLE(10_9, 4_0);
- (void)mapView:(MKMapView *)mapView didUpdateUserLocation:(MKUserLocation *)userLocation NS_AVAILABLE(10_9, 4_0);
- (void)mapView:(MKMapView *)mapView didFailToLocateUserWithError:(NSError *)error NS_AVAILABLE(10_9, 4_0);

- (void)mapView:(MKMapView *)mapView annotationView:(MKAnnotationView *)view didChangeDragState:(MKAnnotationViewDragState)newState 
   fromOldState:(MKAnnotationViewDragState)oldState NS_AVAILABLE(10_9, 4_0);

#if TARGET_OS_IPHONE
- (void)mapView:(MKMapView *)mapView didChangeUserTrackingMode:(MKUserTrackingMode)mode animated:(BOOL)animated NS_AVAILABLE(NA, 5_0);
#endif

- (MKOverlayRenderer *)mapView:(MKMapView *)mapView rendererForOverlay:(id <MKOverlay>)overlay NS_AVAILABLE(10_9, 7_0);
- (void)mapView:(MKMapView *)mapView didAddOverlayRenderers:(NSArray<MKOverlayRenderer *> *)renderers NS_AVAILABLE(10_9, 7_0);

#if TARGET_OS_IPHONE
// Prefer -mapView:rendererForOverlay:
- (MKOverlayView *)mapView:(MKMapView *)mapView viewForOverlay:(id <MKOverlay>)overlay NS_DEPRECATED_IOS(4_0, 7_0);
// Called after the provided overlay views have been added and positioned in the map.
// Prefer -mapView:didAddOverlayRenderers:
- (void)mapView:(MKMapView *)mapView didAddOverlayViews:(NSArray *)overlayViews NS_DEPRECATED_IOS(4_0, 7_0);
#endif

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKPolylineView.h
//
//  MKPolylineView.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <MapKit/MKPolyline.h>
#import <MapKit/MKOverlayPathView.h>
#import <MapKit/MKFoundation.h>

// Prefer MKPolylineRenderer
MK_CLASS_AVAILABLE(NA, 4_0) __WATCHOS_PROHIBITED
@interface MKPolylineView : MKOverlayPathView

- (instancetype)initWithPolyline:(MKPolyline *)polyline NS_DEPRECATED_IOS(4_0, 7_0);

@property (nonatomic, readonly) MKPolyline *polyline NS_DEPRECATED_IOS(4_0, 7_0);

@end
// ==========  MapKit.framework/Headers/MKOverlayView.h
//
//  MKOverlayView.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MKGeometry.h>
#import <MapKit/MKOverlay.h>
#import <MapKit/MKFoundation.h>


// Prefer MKOverlayRenderer
MK_CLASS_AVAILABLE(NA, 4_0) __WATCHOS_PROHIBITED
@interface MKOverlayView : UIView

- (instancetype)initWithOverlay:(id <MKOverlay>)overlay NS_DESIGNATED_INITIALIZER NS_DEPRECATED_IOS(4_0, 7_0);

@property (nonatomic, readonly) id <MKOverlay> overlay NS_DEPRECATED_IOS(4_0, 7_0);

// Convert screen points relative to this view to absolute MKMapPoints
- (CGPoint)pointForMapPoint:(MKMapPoint)mapPoint NS_DEPRECATED_IOS(4_0, 7_0);
- (MKMapPoint)mapPointForPoint:(CGPoint)point NS_DEPRECATED_IOS(4_0, 7_0);

- (CGRect)rectForMapRect:(MKMapRect)mapRect NS_DEPRECATED_IOS(4_0, 7_0);
- (MKMapRect)mapRectForRect:(CGRect)rect NS_DEPRECATED_IOS(4_0, 7_0);

// Return YES if the view is currently ready to draw in the specified rect.
// Return NO if the view will not draw in the specified rect or if the
// data necessary to draw in the specified rect is not available.  In the 
// case where the view may want to draw in the specified rect but the data is
// not available, use setNeedsDisplayInMapRect:zoomLevel: to signal when the
// data does become available.
- (BOOL)canDrawMapRect:(MKMapRect)mapRect
             zoomScale:(MKZoomScale)zoomScale NS_DEPRECATED_IOS(4_0, 7_0);

- (void)drawMapRect:(MKMapRect)mapRect
          zoomScale:(MKZoomScale)zoomScale
          inContext:(CGContextRef)context NS_DEPRECATED_IOS(4_0, 7_0);

- (void)setNeedsDisplayInMapRect:(MKMapRect)mapRect NS_DEPRECATED_IOS(4_0, 7_0);

- (void)setNeedsDisplayInMapRect:(MKMapRect)mapRect
                       zoomScale:(MKZoomScale)zoomScale NS_DEPRECATED_IOS(4_0, 7_0);

@end

// Road widths are typically not drawn to scale on the map.  This function
// returns the approximate width in points of roads at the specified zoomScale.
// The result of this function is suitable for use with CGContextSetLineWidth.
MK_EXTERN CGFloat MKRoadWidthAtZoomScale(MKZoomScale zoomScale) NS_AVAILABLE(10_9, 4_0) __WATCHOS_PROHIBITED;
// ==========  MapKit.framework/Headers/MKShape.h
//
//  MKShape.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKAnnotation.h>

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 4_0) __WATCHOS_PROHIBITED
@interface MKShape : NSObject <MKAnnotation>

@property (nonatomic, copy, nullable) NSString *title;
@property (nonatomic, copy, nullable) NSString *subtitle;

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKOverlayPathRenderer.h
//
//  MKOverlayPathRenderer.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKOverlayRenderer.h>
#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 7_0) __WATCHOS_PROHIBITED
@interface MKOverlayPathRenderer : MKOverlayRenderer

#if TARGET_OS_IPHONE
@property (strong, nullable) UIColor *fillColor;
@property (strong, nullable) UIColor *strokeColor;
#else
@property (strong, nullable) NSColor *fillColor;
@property (strong, nullable) NSColor *strokeColor;
#endif

@property CGFloat lineWidth; // defaults to 0, which is MKRoadWidthAtZoomScale(currentZoomScale)
@property CGLineJoin lineJoin; // defaults to kCGLineJoinRound
@property CGLineCap lineCap; // defaults to kCGLineCapRound
@property CGFloat miterLimit; // defaults to 10
@property CGFloat lineDashPhase; // defaults to 0
@property (copy, nullable) NSArray<NSNumber *> *lineDashPattern; // defaults to nil

// subclassers should override this to create a path and then set it on
// themselves with self.path = newPath;
- (void)createPath;
// returns cached path or calls createPath if path has not yet been created
@property (null_resettable) CGPathRef path; // path will be retained
- (void)invalidatePath;

// subclassers may override these
- (void)applyStrokePropertiesToContext:(CGContextRef)context
                           atZoomScale:(MKZoomScale)zoomScale;
- (void)applyFillPropertiesToContext:(CGContextRef)context
                         atZoomScale:(MKZoomScale)zoomScale;
- (void)strokePath:(CGPathRef)path inContext:(CGContextRef)context;
- (void)fillPath:(CGPathRef)path inContext:(CGContextRef)context;

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKDirections.h
//
//  MKDirections.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

@class MKDirectionsRequest;
@class MKDirectionsResponse;
@class MKETAResponse;

NS_ASSUME_NONNULL_BEGIN

typedef void (^MKDirectionsHandler)(MKDirectionsResponse * __nullable response, NSError * __nullable error);
typedef void (^MKETAHandler)(MKETAResponse * __nullable response, NSError * __nullable error);

MK_CLASS_AVAILABLE(10_9, 7_0) __WATCHOS_PROHIBITED
@interface MKDirections : NSObject

// The request will be copied during initialization, so any changes made to the request
// after this method returns do not affect the request used in -calculateDirectionsWithCompletionHandler:
- (instancetype)initWithRequest:(MKDirectionsRequest *)request NS_DESIGNATED_INITIALIZER;

// Any calls to -calculateDirectionsWithCompletionHandler: or calculateETAWithCompletionHandler
// while -[MKDirections isCalculating] will fail. completionHandler will be called on the main queue
- (void)calculateDirectionsWithCompletionHandler:(MKDirectionsHandler)completionHandler;
- (void)calculateETAWithCompletionHandler:(MKETAHandler)completionHandler;
- (void)cancel;

@property (nonatomic, readonly, getter=isCalculating) BOOL calculating;

@end

NS_ASSUME_NONNULL_END
// ==========  MapKit.framework/Headers/MKMapSnapshot.h
//
//  MKMapSnapshot.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIImage.h>
#else
#import <AppKit/AppKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 7_0) __WATCHOS_PROHIBITED
@interface MKMapSnapshot : NSObject

#if TARGET_OS_IPHONE
@property (nonatomic, readonly) UIImage *image;
- (CGPoint)pointForCoordinate:(CLLocationCoordinate2D)coordinate;
#else
@property (nonatomic, readonly) NSImage *image;
- (NSPoint)pointForCoordinate:(CLLocationCoordinate2D)coordinate;
#endif

@end

NS_ASSUME_NONNULL_END
