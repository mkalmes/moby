// ==========  PDFKit.framework/Headers/PDFAnnotation.h
//
//  PDFAnnotation.h
//  Copyright � 2016 Apple. All rights reserved.
//
//  PDFAnnotation is a wrapper class of all annotation types for a PDF document.
//  It is a container of key-value pairs that map directly to the PDF file format, defined
//  in the Adobe PDF Specification (file format version 1.7). You can manipulate
//  properties of an annotation by either assigning key-value pairs, where keys are always
//  strings defined in the specification and listed below (example: PDFAnnotationKeyFlags).
//  You can also replace existing key-values in the PDFAnnotation dictionary, or remove them.
//  Value types vary based on what the key is. For example, the value for a color key can either
//  be an array of numbers (0 for no color, 1 for gray, 3 for RGB, 4 for CMYK) or can be an
//  NSColor or UIColor instance. Some keys require complex values, typically as an array or
//  dictionaries of objects. PDFKit provides some classes as a convenience for these complex
//  type: PDFBorder, PDFAction (its subclasses), PDFDestination. Note that there are also
//  helper category functions that are specialized for many of the legacy PDFAnnotation
//  subclasses. You can find this in PDFAnnotationUtilities.h
//
//  Note that the preferred constructor for PDFAnnotation is -[initWithBounds:forType:withProperties:],
//  and at a minimum you must set bounds and type for the annotation. Calling -[init] will raise an
//  exception. To add an annotation to a page, you must do so via -[PDFPage addAnnotation:] on your
//  desired page. You may not change annotation subtype at runtime. If you want to change annotation
//  subtype, remove the annotation and add a new instance. If you use the deprecated constructor
//  -[initWithBounds:], you may set the annotation subtype only once. Any future assignments of subtype
//  will be ignored and produce a warning.
//
//  Note that PDFAnnotation can render any annotation with a content-stream entry in the annotation's
//  dictionary, though some are supported natively based on their annotation dictionary. Supported
//  annotations have their subtype declared via NSString defined in PDFAnnotationUtilities.h
//  using the naming convention "PDFAnnotationSubtypeX", where X is the subtype. Those not in
//  this list will only draw if there is an appearance stream.
//
//  Adobe PDF Specification (1.7) defines in Table 8.15 "Entries common to all annotation
//  dictionaries" 14 common properties among all annotations. 2-4 are required, the rest are
//  optional. PDFKit supports 13 of these annotations. For all common properties and each
//  annotation's specific properties, we define them as enumerations and enum-mapped strings at
//  the top of this file.
//
//  You can activate logging of any annotation key-value assignments that fails by setting the
//  environment variable "PDFKIT_LOG_ANNOTATIONS" to any value.
//

#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFPage.h>
#import <PDFKit/PDFAction.h>

NS_ASSUME_NONNULL_BEGIN

// All PDF annotation subtypes that PDFKit can render: based on Adobe PDF specification, Table 8.20: Annotation types.
// Annotation subtypes not supported: Polygon, PolyLine, Squiggly, Caret, Caret, FileAttachment,
// Sound, Movie, Screen, PrinterMark, TrapNet, Watermark, 3D, Rect.
typedef NSString* const PDFAnnotationSubtype NS_STRING_ENUM;

// Common keys used for all annotations
// Adobe PDF Specification (1.7), Table 8.15: Entries common to all annotation dictionaries
typedef NSString* const PDFAnnotationKey NS_STRING_ENUM;

PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyAppearanceDictionary PDFKIT_AVAILABLE(10_13, 11_0);              // "/AP": Dictionary
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyAppearanceState PDFKIT_AVAILABLE(10_13, 11_0);                   // "/AS": Name
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyBorder PDFKIT_AVAILABLE(10_13, 11_0);                            // "/Border": Array of Integers; or a PDFBorder object
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyColor PDFKIT_AVAILABLE(10_13, 11_0);                             // "/C": Array of Floats; or a PDFKitPlatformColor object
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyContents PDFKIT_AVAILABLE(10_13, 11_0);                          // "/Contents": String
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyFlags PDFKIT_AVAILABLE(10_13, 11_0);                             // "/F": Integer
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyDate PDFKIT_AVAILABLE(10_13, 11_0);                              // "/M": Date or String
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyName PDFKIT_AVAILABLE(10_13, 11_0);                              // "/NM": String
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyPage PDFKIT_AVAILABLE(10_13, 11_0);                              // "/P": Dictionary; or a PDFPage object.
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyRect PDFKIT_AVAILABLE(10_13, 11_0);                              // "/Rect": CGRect
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeySubtype PDFKIT_AVAILABLE(10_13, 11_0);                           // "/Subtype": Name (See Table 8.20: Annotation types)

// Additional annotation extensions...
// Adobe PDF Specification (1.7), Table 8.23: Additional entries specific to a text annotation
// Adobe PDF Specification (1.7), Table 8.24: Additional entries specific to a link annotation
// Adobe PDF Specification (1.7), Table 8.25: Additional entries specific to a free text annotation
// Adobe PDF Specification (1.7), Table 8.26: Additional entries specific to a line annotation
// Adobe PDF Specification (1.7), Table 8.28: Additional entries specific to a square or circle annotation
// Adobe PDF Specification (1.7), Table 8.30: Additional entries specific to text markup annotations (highlight, underline, strikeout)
// Adobe PDF Specification (1.7), Table 8.32: Additional entries specific to a rubber stamp annotation
// Adobe PDF Specification (1.7), Table 8.33: Additional entries specific to an ink annotation
// Adobe PDF Specification (1.7), Table 8.34: Additional entries specific to a pop-up annotation
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyAction PDFKIT_AVAILABLE(10_13, 11_0);                            // "/A": Dictionary; or a PDFAction object
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyAdditionalActions PDFKIT_AVAILABLE(10_13, 11_0);                 // "/AA": Dictionary; or a PDFAction object
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyBorderStyle PDFKIT_AVAILABLE(10_13, 11_0);                       // "/BS": Dictionary
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyDefaultAppearance PDFKIT_AVAILABLE(10_13, 11_0);                 // "/DA": String
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyDestination PDFKIT_AVAILABLE(10_13, 11_0);                       // "/Dest": Array, Name, or String
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyHighlightingMode PDFKIT_AVAILABLE(10_13, 11_0);                  // "/H": Name
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyInklist PDFKIT_AVAILABLE(10_13, 11_0);                           // "/Inklist": Array of Arrays (each array representing a stroked path)
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyInteriorColor PDFKIT_AVAILABLE(10_13, 11_0);                     // "/IC": Array of Floats; or a PDFKitPlatformColor object
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyLinePoints PDFKIT_AVAILABLE(10_13, 11_0);                        // "/L": Array of Floats
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyLineEndingStyles PDFKIT_AVAILABLE(10_13, 11_0);                  // "/LE": Array of Strings
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyIconName PDFKIT_AVAILABLE(10_13, 11_0);                          // "/Name": Name
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyOpen PDFKIT_AVAILABLE(10_13, 11_0);                              // "/Open": Boolean
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyParent PDFKIT_AVAILABLE(10_13, 11_0);                            // "/Parent": Dictionary; or a PDFAnnotation object
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyPopup PDFKIT_AVAILABLE(10_13, 11_0);                             // "/Popup": Dictionary; or a PDFAnnotation object of type "Popup"
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyQuadding PDFKIT_AVAILABLE(10_13, 11_0);                          // "/Q": Integer
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyQuadPoints PDFKIT_AVAILABLE(10_13, 11_0);                        // "/QuadPoints": Array of Floats
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyTextLabel PDFKIT_AVAILABLE(10_13, 11_0);                         // "/T": String

// Widget annotation extensions
// Adobe PDF Specification (1.7), Table 8.39: Additional entries specific to a widget annotation
// Adobe PDF Specification (1.7), Table 8.40: Entries in an appearance characteristics dictionary
// Adobe PDF Specification (1.7), Table 8.69: Entries common to all field dictionaries
// Adobe PDF Specification (1.7), Table 8.76: Additional entry specific to check box and radio button fields
// Adobe PDF Specification (1.7), Table 8.78: Additional entry specific to a text field
// Adobe PDF Specification (1.7), Table 8.80: Additional entries specific to a choice field
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetDownCaption PDFKIT_AVAILABLE(10_13, 11_0);                 // "/AC": String
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetBorderColor PDFKIT_AVAILABLE(10_13, 11_0);                 // "/BC": Array of Floats; or a PDFKitPlatformColor object
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetBackgroundColor PDFKIT_AVAILABLE(10_13, 11_0);             // "/BG": Array of Floats; or a PDFKitPlatformColor object
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetCaption PDFKIT_AVAILABLE(10_13, 11_0);                     // "/CA": String
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetDefaultValue PDFKIT_AVAILABLE(10_13, 11_0);                // "/DV": (various)
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetFieldFlags PDFKIT_AVAILABLE(10_13, 11_0);                  // "/Ff": Integer
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetFieldType PDFKIT_AVAILABLE(10_13, 11_0);                   // "/FT": Name
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetAppearanceDictionary PDFKIT_AVAILABLE(10_13, 11_0);        // "/MK": Dictionary; or PDFAppearanceCharacteristics object
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetMaxLen PDFKIT_AVAILABLE(10_13, 11_0);                      // "/MaxLen": Integer
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetOptions PDFKIT_AVAILABLE(10_13, 11_0);                     // "/Opt": Array (each element is either a string, or an array of two strings)
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetRotation PDFKIT_AVAILABLE(10_13, 11_0);                    // "/R": Integer
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetRolloverCaption PDFKIT_AVAILABLE(10_13, 11_0);             // "/RC": String
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetTextLabelUI PDFKIT_AVAILABLE(10_13, 11_0);                 // "/TU": String
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetValue PDFKIT_AVAILABLE(10_13, 11_0);                       // "/V": (various)

@class PDFAction, PDFBorder, PDFPage, PDFAnnotationPopup, PDFAnnotationPrivateVars;

PDFKIT_CLASS_AVAILABLE(10_4, 11_0)
@interface PDFAnnotation : NSObject <NSCopying, NSCoding>
{
@private
    PDFAnnotationPrivateVars *_private;
}

// This is the base class for all annotations. A PDFAnnotation object by itself is not useful, only subclasses (like 
// PDFAnnotationCircle, PDFAnnotationText) are interesting. In parsing a PDF however, any unknown or unsupported 
// annotations will be represented as this base class.

// -------- initializer

// Create a custom annotation with bounds, a type (PDFAnnotationSubtype), and an (optional) dictionary of annotation properties.
- (instancetype)initWithBounds:(PDFRect)bounds forType:(PDFAnnotationSubtype)annotationType withProperties:(nullable NSDictionary*)properties PDFKIT_AVAILABLE(10_13, 11_0) NS_DESIGNATED_INITIALIZER;

// -------- accessors

// Returns the page the annotation is associated with (may return nil if annotation not associated with a page).
@property (nonatomic, weak, nullable) PDFPage *page;

// Returns the annotation type (called "Subtype" in the PDF specification since "Annot" is the type). Examples include: 
// "Text", "Link", "Line", etc. Required. Note that you are only allowed to set the type of an annotation once.
@property (nonatomic, copy, nullable) NSString *type;

// Required for all annotations. The bounding box in page-space of the annotation.
@property (nonatomic) PDFRect bounds;

// Indicates whether the annotation should be displayed on screen (depending upon -[shouldPrint] it may still print).
@property (nonatomic) BOOL shouldDisplay;

// Indicates whether the annotation should be printed or not.
@property (nonatomic) BOOL shouldPrint;

// Optional (-[modificationDate] may return nil). Modification date of the annotation.
@property (nonatomic, copy, nullable) NSDate *modificationDate PDFKIT_AVAILABLE(10_5, 11_0);

// Optional (-[userName] may return nil). Name of the user who created the annotation.
@property (nonatomic, copy, nullable) NSString *userName PDFKIT_AVAILABLE(10_5, 11_0);

// Optional (-[popup] may return nil). Not used with links or widgets, a popup annotation associated with this
// annotation. The bounds and open state of the popup indicate the placement and open state of the popup window.
@property (nonatomic, strong, nullable) PDFAnnotationPopup *popup PDFKIT_AVAILABLE(10_5, 11_0);

// Optional border or border style that describes how to draw the annotation border (if any). For the "geometry"
// annotations (Circle, Ink, Line, Square), the border indicates the line width and whether to draw with a dash pattern
// or solid pattern. PDFAnnotation markup types (Highlight, Strikethrough, Underline) ignores the border.
@property (nonatomic, strong, nullable) PDFBorder *border PDFKIT_AVAILABLE(10_4, 11_0);

// For many annotations ("Circle", "Square") the stroke color. Used for other annotations as well.
@property (nonatomic, copy) PDFKitPlatformColor *color PDFKIT_AVAILABLE(10_4, 11_0);

// A string of text associated with an annotation. Often displayed in a window when the annotation is clicked on
// ("FreeText" and "Text" especially).
@property (nonatomic, copy, nullable) NSString *contents PDFKIT_AVAILABLE(10_5, 11_0);

// Optional action performed when a user clicks / taps an annotation. PDF readers ignore actions except
// for those associated with Link or button Widget annotations.
@property (nonatomic, strong, nullable) PDFAction *action PDFKIT_AVAILABLE(10_5, 11_0);

// Returns YES if the annotation has an appearance stream. Annotations with appearance streams are drawn using their
// stream. As a result setting many parameters (like -[setColor:] above) will have no visible effect.
@property (nonatomic, readonly) BOOL hasAppearanceStream;

// The highlight state dictates how the annotation is drawn. For example, if a user has clicked on a
// "Link" annotation, you should set highlighted to YES and redraw it. When the user lets up, set highlighted to
// NO and redraw again.
@property (nonatomic, getter=isHighlighted) BOOL highlighted PDFKIT_AVAILABLE(10_13, 11_0);

// -------- drawing

// Draw method. Draws in page-space relative to origin of "box" passed in and to the given context
- (void)drawWithBox:(PDFDisplayBox)box inContext:(CGContextRef)context PDFKIT_AVAILABLE(10_12, 11_0);

// -------- attribute mutations

// Allows you to set a key-value pair in this annotation's dictionary. Returns true on successful
// assignment, false on error. Key must be valid for a PDF annotation's object type, and must have
// a value that is acceptable for the key type. These values can either be an NSString, NSNumber,
// NSArray of strings or numbers, or an NSDictionary of the previously listed types. Some keys expect
// a complex type, for example the key "/C" expects a color in the format of an array of 0, 1, 3,
// or 4 elements, with each element being a floating-point number in the range of 0.0 - 1.0 ). As
// a convenience, these kind of keys will directly accept NSColor / UIColor values. Other convenience
// functions provide similar support can be found in PDFAnnotationUtilities header file. Note that you
// can set the environment variable "PDFKIT_LOG_ANNOTATIONS" to log any key-value assignment failures.
- (BOOL)setValue:(id)value forAnnotationKey:(PDFAnnotationKey)key PDFKIT_AVAILABLE(10_12, 11_0);
- (BOOL)setBoolean:(BOOL)value forAnnotationKey:(PDFAnnotationKey)key PDFKIT_AVAILABLE(10_12, 11_0);
- (BOOL)setRect:(PDFRect)value forAnnotationKey:(PDFAnnotationKey)key PDFKIT_AVAILABLE(10_12, 11_0);

// List all key-value pairs for this annotation; returns a deep copy of all pairs.
// Note that this method will not include a copy of the value for /Parent. This is by design as to avoid
// introduing a memory cycle. If you would like to get the /Parent propery, use -[PDFAnnotation valueForAnnotationKey:]
// with key PDFAnnotationKeyParent.
@property (nonatomic, readonly, copy) NSDictionary *annotationKeyValues PDFKIT_AVAILABLE(10_13, 11_0);

// Retrieves a deep copy of the key-value pair based on the given key; key can either be
// from the keys PDFAnnotationKey, or an appropriate string from the PDF specification.
- (nullable id)valueForAnnotationKey:(PDFAnnotationKey)key PDFKIT_AVAILABLE(10_12, 11_0);

// Remove the key-value pair from the annotation dictionary. Returns true on successful removal.
- (void)removeValueForAnnotationKey:(PDFAnnotationKey)key PDFKIT_AVAILABLE(10_12, 11_0);

@end



NS_ASSUME_NONNULL_END
// ==========  PDFKit.framework/Headers/PDFActionResetForm.h
//
//  PDFActionResetForm.h
//  Copyright © 2016 Apple. All rights reserved.
//
//  PDFActionResetForm is an interaction event tied with an annotation. This action
//  allows a user to reset all form fields (associated by their fieldNames) annotations.
//  Form field annotations are typically widget-type annotations.
//

#import <PDFKit/PDFKitPlatform.h>

#import <PDFKit/PDFAction.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFActionResetFormPrivateVars;

PDFKIT_CLASS_AVAILABLE(10_5, 11_0)
@interface PDFActionResetForm : PDFAction <NSCopying>
{
@private
    PDFActionResetFormPrivateVars *_private2;
}

// Initially there will be no fields, and -[fieldsIncludedAreCleared] will be YES.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

// Fields are an array of NSString objects corresponding to the fieldNames of Widget annotations on the page.
// May return nil.
@property (nonatomic, copy, nullable) NSArray<NSString*> *fields;

// If -[fieldsIncludedAreCleared] is YES, then the widget annotations associated with the fieldNames in the fields
// array above are to be cleared, i.e. uncheck checkboxes, clear text fields, reset radio buttons, etc.
// If -[fieldsIncludedAreCleared] is NO, then every widget annotation associated with the fields array is not to be
// cleared, meaning that every widget annotation in the document whose field name is not listed is to be cleared.
// Both situations above only occur when this reset-form action is performed.
@property (nonatomic) BOOL fieldsIncludedAreCleared;

@end

NS_ASSUME_NONNULL_END
// ==========  PDFKit.framework/Headers/PDFAction.h
//
//  PDFAction.h
//  Copyright © 2016 Apple. All rights reserved.
//
//  PDFAction is an abstract class, representing an event a user can trigger through
//  interaction with the owning annotation. These events are PDFActionGoTo, PDFActionNamed,
//  PDFActionRemoveGoTo, PDFActionResetForm, and PDFActionURL. Typically these events
//  are for moving the PDFView view-portal, open a web browser, clear out forms, etc.
//

#import <PDFKit/PDFKitPlatform.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFActionPrivate;

PDFKIT_CLASS_AVAILABLE(10_5, 11_0)
@interface PDFAction : NSObject <NSCopying>
{
@private
    PDFActionPrivate *_private;
}

// Type of action.  These won't always correspond to the PDFAction subclass in the way you might expect.  For example, 
// a PDFActionURL may return "URI" or "Launch" depending upon the original action (as defined in the PDF spec. - for 
// the PDFKit API we decided to handle the two actions within the same class and also use the more familiar 'URL' term 
// rather than 'URI').
// Type based on the Adobe PDF Specification (1.7), Table 8.48: Action types.
@property (nonatomic, readonly) NSString *type;

@end

NS_ASSUME_NONNULL_END
// ==========  PDFKit.framework/Headers/PDFActionRemoteGoTo.h
//
//  PDFActionRemoteGoTo.h
//  Copyright © 2016 Apple. All rights reserved.
//
//  PDFActionRemoteGoTo is an interaction event tied with an annotation. This action
//  is the same action type as PDFActionGoTo, but references another document, allowing
//  you to jump to specific pages or positions in other PDF files.
//

#import <PDFKit/PDFKitPlatform.h>

#import <PDFKit/PDFAction.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFActionRemoteGoToPrivateVars;

PDFKIT_CLASS_AVAILABLE(10_5, 11_0)
@interface PDFActionRemoteGoTo : PDFAction <NSCopying>
{
@private
    PDFActionRemoteGoToPrivateVars *_private2;
}

// As with the calls below, note that PDFActionRemoteGoTo uses a zero-based page index and not a PDFPage object.
// This simplifies dealing with remote destinations for documents that may not be instantiated.
- (instancetype)initWithPageIndex:(NSUInteger)pageIndex atPoint:(PDFPoint)point fileURL:(NSURL *)url NS_DESIGNATED_INITIALIZER;

// Get and set the page index (zero-based) referenced by the action.
@property (nonatomic) NSUInteger pageIndex;

// Get and set the point on the above page referenced by the action.  Just like PDFDestination a value of 
// kPDFDestinationUnspecifiedValue for the x or the y of the point indicates that no position is specified.
@property (nonatomic) PDFPoint point;

// Get and set the URL of the document referenced from the action.
@property (nonatomic, copy) NSURL *URL;

@end

NS_ASSUME_NONNULL_END
// ==========  PDFKit.framework/Headers/PDFActionGoTo.h
//
//  PDFActionGoto.h
//  Copyright © 2016 Apple. All rights reserved.
//
//  PDFActionGoTo is an interaction event tied with an annotation. This action
//  allows the user to jump to a PDFDestination, which is typically a position
//  on a page paired with a zoom factor.
//

#import <PDFKit/PDFKitPlatform.h>

#import <PDFKit/PDFAction.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFDestination, PDFActionGoToPrivateVars;

PDFKIT_CLASS_AVAILABLE(10_5, 11_0)
@interface PDFActionGoTo : PDFAction <NSCopying>
{
@private
    PDFActionGoToPrivateVars *_private2;
}

- (instancetype)initWithDestination:(PDFDestination *)destination NS_DESIGNATED_INITIALIZER;

@property (nonatomic, strong) PDFDestination *destination;

@end

NS_ASSUME_NONNULL_END
// ==========  PDFKit.framework/Headers/PDFAppearanceCharacteristics.h
//
//  PDFAppearanceCharacteristics.h
//  Copyright © 2017 Apple. All rights reserved.
//
//  PDFAppearanceCharacteristics represents a dictionary that is specific to widget annotation types,
//  containing additional information for constructing the annotation’s appearance.
//  It is designed to be a representation of the /MK appearance characteristics entry in
//  the annotation dictionary. Because the /MK entry is optional, all properties of
//  PDFAppearanceCharacteristics are optional as well.
//
//  Properties are based on the Adobe PDF Specification (1.7),
//  Table 8.40: Entries in an appearance characteristics dictionary
//

#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFAnnotationUtilities.h>

NS_ASSUME_NONNULL_BEGIN

// Widget appearance characteristics keys.
typedef NSString* const PDFAppearanceCharacteristicsKey NS_STRING_ENUM;

PDFKIT_EXTERN PDFAppearanceCharacteristicsKey PDFAppearanceCharacteristicsKeyBackgroundColor PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAppearanceCharacteristicsKey PDFAppearanceCharacteristicsKeyBorderColor PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAppearanceCharacteristicsKey PDFAppearanceCharacteristicsKeyRotation PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAppearanceCharacteristicsKey PDFAppearanceCharacteristicsKeyCaption PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAppearanceCharacteristicsKey PDFAppearanceCharacteristicsKeyRolloverCaption PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAppearanceCharacteristicsKey PDFAppearanceCharacteristicsKeyDownCaption PDFKIT_AVAILABLE(10_13, 11_0);

@class PDFAppearanceCharacteristicsPrivate;

PDFKIT_CLASS_AVAILABLE(10_13, 11_0)
@interface PDFAppearanceCharacteristics : NSObject <NSCopying>
{
@private
    PDFAppearanceCharacteristicsPrivate *_private;
}

// -------- accessors

// For button widget annotations, need to specify the control type for PDFAppearanceCharacteristics
// as certain attributes, i.e. captions, are only available for certain flavors.
// Control type does not need to be set for text or choice widget annotations.
@property (nonatomic) PDFWidgetControlType controlType;

// The background color of the widget annotation.
@property (nonatomic, copy, nullable) PDFKitPlatformColor *backgroundColor;

// The border color of the widget annotation.
@property (nonatomic, copy, nullable) PDFKitPlatformColor *borderColor;

// The number of *degrees* by which the widget annotation is rotated counterclockwise relative to the page.
// The value must be a multiple of 90. Default value: 0.
@property (nonatomic) NSInteger rotation;

// The widget annotation’s normal caption, displayed when it is not interacting with the user.
@property (nonatomic, copy, nullable) NSString *caption;

// The widget's caption displayed when the user moves the mouse over the annotation.
// Applies only to kPDFWidgetPushButtonControl.
@property (nonatomic, copy, nullable) NSString *rolloverCaption;

// The widget's caption displayed when the user holds the mouse button while over the annotation.
// Applies only to kPDFWidgetPushButtonControl.
@property (nonatomic, copy, nullable) NSString *downCaption;

// List all appearance characteristics properties as key-value pairs; returns a deep copy of all pairs.
// Helpful for debugging.
@property (nonatomic, readonly, copy) NSDictionary *appearanceCharacteristicsKeyValues;


@end

NS_ASSUME_NONNULL_END
// ==========  PDFKit.framework/Headers/PDFDestination.h
//
//  PDFDestination.h
//  Copyright © 2016 Apple. All rights reserved.
//
//  PDFDestination represents a dictionary used in annotations, typically as
//  a property for an action. Destinations are a coordinate and zoom factor
//  for a specific page in a document.
//

#import <PDFKit/PDFKitPlatform.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFPage, PDFDestinationPrivate;

// To specify a destination point where you don't care about the x or y value (or either), use this value.
PDFKIT_EXTERN const CGFloat kPDFDestinationUnspecifiedValue PDFKIT_AVAILABLE(10_4, 11_0);

PDFKIT_CLASS_AVAILABLE(10_4, 11_0)
@interface PDFDestination : NSObject <NSCopying>
{
@private
    PDFDestinationPrivate *_private;
}

// -------- initializer

// Initializer. You do not often create PDFDestinations, but usually get them from link annotations or PDFOutline items.
- (instancetype)initWithPage:(PDFPage *)page atPoint:(PDFPoint)point NS_DESIGNATED_INITIALIZER;

// -------- accessors

// The page that the destination refers to (destination page).
@property (nonatomic, weak, readonly) PDFPage *page;

// The destination point on the page above (in page space).
@property (nonatomic, readonly) PDFPoint point;

// Get / set the scale factor the PDF viewer should assume for this destination.
// kPDFDestinationUnspecifiedValue indicates the scale factor is unaffected.
@property (nonatomic) CGFloat zoom PDFKIT_AVAILABLE(10_7, 11_0);

// If the destination passed in is further along in the document than the receiver, we return NSOrderedAscending. If
// the destination passed in precedes the receiver, we return NSOrderedDescending. Otherwise if the destination passed in
// matches the receiver, we return NSOrderedSame. For purposes of comparison, the horizontal component on the point is
// ignored. Also for purposes of comparison, having kPDFDestinationUnspecifiedValue for the vertical component of the
// destination point will be treated as the top point on the destination page.
// An exception will be raised if either destination does not have a page associated with it or if the pages of the two
// destinations are associated with different documents.
- (NSComparisonResult)compare:(PDFDestination *)destination PDFKIT_AVAILABLE(10_5, 11_0);

@end

NS_ASSUME_NONNULL_END
// ==========  PDFKit.framework/Headers/PDFActionNamed.h
//
//  PDFActionNamed.h
//  Copyright © 2016 Apple. All rights reserved.
//
//  PDFActionNamed is an interaction event tied with an annotation. This action
//  allows the user to change their navigation stack or their current view. This
//  can manipulate the user's navigation stack (move to the previous page, next page etc.),
//  trigger some other forms of interactions (string search, printing, etc.), and
//  manipulate the current view (change zoom factors).
//

#import <PDFKit/PDFKitPlatform.h>

#import <PDFKit/PDFAction.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFActionNamedPrivateVars;

// Action names.
PDFKIT_ENUM_AVAILABLE(10_5, 11_0)
typedef NS_ENUM(NSInteger, PDFActionNamedName)
{
    kPDFActionNamedNone = 0, 
    kPDFActionNamedNextPage = 1, 
    kPDFActionNamedPreviousPage = 2, 
    kPDFActionNamedFirstPage = 3, 
    kPDFActionNamedLastPage = 4, 
    kPDFActionNamedGoBack = 5, 
    kPDFActionNamedGoForward = 6, 
    kPDFActionNamedGoToPage = 7, 
    kPDFActionNamedFind = 8, 
    kPDFActionNamedPrint = 9, 
    kPDFActionNamedZoomIn = 10, 
    kPDFActionNamedZoomOut = 11
};

PDFKIT_CLASS_AVAILABLE(10_5, 11_0)
@interface PDFActionNamed : PDFAction <NSCopying>
{
@private
    PDFActionNamedPrivateVars *_private2;
}

- (instancetype)initWithName:(PDFActionNamedName)name NS_DESIGNATED_INITIALIZER;

@property (nonatomic) PDFActionNamedName name;

@end

NS_ASSUME_NONNULL_END
// ==========  PDFKit.framework/Headers/PDFActionURL.h
//
//  PDFActionURL.h
//  Copyright © 2016 Apple. All rights reserved.
//
//  PDFActionURL is an interaction event tied with an annotation. This action allows
//  the user to open a URL, either being a local file or web URL.
//

#import <PDFKit/PDFAction.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFActionURLPrivateVars;

PDFKIT_CLASS_AVAILABLE(10_5, 11_0)
@interface PDFActionURL : PDFAction <NSCopying>
{
@private
    PDFActionURLPrivateVars *_private2;
}

- (instancetype)initWithURL:(NSURL *)url NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy) NSURL *URL;

@end

NS_ASSUME_NONNULL_END
// ==========  PDFKit.framework/Headers/PDFThumbnailView.h
//
//  PDFThumbnailView.h
//  Copyright © 2016 Apple. All rights reserved.
//
//  PDFThumbnailView is a custom view that contains a set of PDFPage thumbnails
//  that a user can scroll over, interact with, and have these interactions drive
//  view changes on PDFView.
//

#import <PDFKit/PDFKitPlatform.h>

NS_ASSUME_NONNULL_BEGIN

// Layout mode for thumbnail view.
PDFKIT_ENUM_AVAILABLE(NA, 11_0)
typedef NS_ENUM(NSInteger, PDFThumbnailLayoutMode)
{
    PDFThumbnailLayoutModeVertical = 0,
    PDFThumbnailLayoutModeHorizontal = 1
};

@class PDFView, PDFPage, PDFThumbnailViewPrivateVars;

// Notification when PDFDocument is modified.
PDFKIT_EXTERN NSString *PDFThumbnailViewDocumentEditedNotification PDFKIT_AVAILABLE(10_4, 11_0);

PDFKIT_CLASS_AVAILABLE(10_5, 11_0)
@interface PDFThumbnailView : PDFKitPlatformView <NSCoding>
{
@private
    PDFThumbnailViewPrivateVars *_private;
}

// PDFView associated with the thumbnail view.
@property (nonatomic, strong, nullable) PDFView *PDFView;

// Background color of view.
@property (nonatomic, copy, nullable) PDFKitPlatformColor *backgroundColor;

// This will return only a single page unless allowsMultipleSelection is set to YES.
@property (nonatomic, readonly, strong, nullable) NSArray<PDFPage*> *selectedPages;

// The maximum thumbnail size.
@property (nonatomic) PDFSize thumbnailSize;


// Defines if the thumbnail view is to be displayed vertically or horizontally.
// Default PDFThumbnailLayoutModeVertical.
@property (nonatomic) PDFThumbnailLayoutMode layoutMode PDFKIT_AVAILABLE(NA, 11_0);

// Default UIEdgeInsetsZero. Add additional scroll area around content
@property (nonatomic) UIEdgeInsets contentInset PDFKIT_AVAILABLE(NA, 11_0);


@end

NS_ASSUME_NONNULL_END
// ==========  PDFKit.framework/Headers/PDFBorder.h
//
//  PDFBorder.h
//  Copyright © 2016 Apple. All rights reserved.
//
//  PDFBorder represents an array structure that is common for graphical annotations,
//  defining properties like line-stroke width, color, and dashed patterns.
//  It is designed to be a representation of the /BS entry in the annotation dictionary.
//
//  Properties are based on the Adobe PDF Specification (1.7)
//  Table 8.17: Entries in a border style dictionary.
//

#import <PDFKit/PDFKitPlatform.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFBorderPrivateVars;

// Style in which PDFBorder is displayed.
PDFKIT_ENUM_AVAILABLE(10_4, 11_0)
typedef NS_ENUM(NSInteger, PDFBorderStyle)
{
    kPDFBorderStyleSolid = 0, 
    kPDFBorderStyleDashed = 1, 
    kPDFBorderStyleBeveled = 2, 
    kPDFBorderStyleInset = 3, 
    kPDFBorderStyleUnderline = 4
};

// Border style dictionary keys.
typedef NSString* const PDFBorderKey NS_STRING_ENUM;

PDFKIT_EXTERN PDFBorderKey PDFBorderKeyLineWidth PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFBorderKey PDFBorderKeyStyle PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFBorderKey PDFBorderKeyDashPattern PDFKIT_AVAILABLE(10_13, 11_0);

// PDFBorder is not directly an annotation, but instead is a supportive structure common to a few annotations.
PDFKIT_CLASS_AVAILABLE(10_4, 11_0)
@interface PDFBorder : NSObject <NSCopying, NSCoding>
{
@private
	PDFBorderPrivateVars *_private;
}

// -------- accessors

// See styles above. Whether border is drawn solid, dashed etc.
@property (nonatomic) PDFBorderStyle style;

// Width of line used to stroke border.
@property (nonatomic) CGFloat lineWidth;

// Array of floats specifying the dash pattern (see NSBezierPath for more detail).
@property (nonatomic, copy, nullable) NSArray *dashPattern;

// List all border properties as key-value pairs; returns a deep copy of all pairs. Helpful for debugging.
@property (nonatomic, readonly, copy) NSDictionary *borderKeyValues;

// Draw method. Not generally needed since the annotations themselves call this method when they are drawn.
// Call -[NSColor set] before calling (the various annotations do this often calling -[PDFAnnotation color] or whatever 
// is appropriate for their class.
- (void)drawInRect:(PDFRect)rect;

@end

NS_ASSUME_NONNULL_END
// ==========  PDFKit.framework/Headers/PDFView.h
//
//  PDFView.h
//  Copyright © 2016 Apple. All rights reserved.
//
//  This class is the main view of PDFKit: you can instantiate a PDFView or create one
//  in Interface Builder that will host the contents of a PDFDocument. Note that you can
//  layout the pages of a PDFDocument in a few different ways, mostly as a function of
//  PDFDisplayMode, combined with a few options like "displayDirection" and "displaysRTL".
//  Note the delegate PDFViewDelegate and associated notifications, both of which can be
//  used as a way to listen for search, print, and user-interaction events.
//

#import <PDFKit/PDFKitPlatform.h>

#import <PDFKit/PDFDocument.h>
#import <PDFKit/PDFPage.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFAction, PDFActionRemoteGoTo, PDFDestination, PDFSelection, PDFViewPrivate;
@protocol PDFViewDelegate;

// Display modes.
PDFKIT_ENUM_AVAILABLE(10_4, 11_0)
typedef NS_ENUM(NSInteger, PDFDisplayMode)
{
    kPDFDisplaySinglePage = 0, 
    kPDFDisplaySinglePageContinuous = 1, 
    kPDFDisplayTwoUp = 2, 
    kPDFDisplayTwoUpContinuous = 3
};

// Display direction.
PDFKIT_ENUM_AVAILABLE(10_13, 11_0)
typedef NS_ENUM(NSInteger, PDFDisplayDirection)
{
    kPDFDisplayDirectionVertical = 0,
    kPDFDisplayDirectionHorizontal = 1,
};

// PDF areas of interest (bitfield, multiple bits below may be set).
PDFKIT_AVAILABLE(10_4, 11_0)
typedef NS_OPTIONS(NSInteger, PDFAreaOfInterest)
{
    kPDFNoArea =            0,
    kPDFPageArea =          (1UL << 0),
    kPDFTextArea =          (1UL << 1),
    kPDFAnnotationArea =    (1UL << 2),
    kPDFLinkArea =          (1UL << 3),
    kPDFControlArea =       (1UL << 4),
    kPDFTextFieldArea =     (1UL << 5),
    kPDFIconArea =          (1UL << 6),
    kPDFPopupArea =         (1UL << 7),
    kPDFImageArea =         (1UL << 8),
};

// Interpolation quality.
PDFKIT_ENUM_AVAILABLE(10_7, 11_0)
typedef NS_ENUM(NSInteger, PDFInterpolationQuality)
{
    kPDFInterpolationQualityNone = 0, 
    kPDFInterpolationQualityLow = 1, 
    kPDFInterpolationQualityHigh = 2
};

// Notifications.
PDFKIT_EXTERN NSNotificationName const PDFViewDocumentChangedNotification PDFKIT_AVAILABLE(10_4, 11_0);       // Notification when a new document is associated with view.
PDFKIT_EXTERN NSNotificationName const PDFViewChangedHistoryNotification PDFKIT_AVAILABLE(10_4, 11_0);        // Notification when the page history changes.
PDFKIT_EXTERN NSNotificationName const PDFViewPageChangedNotification PDFKIT_AVAILABLE(10_4, 11_0);           // Notification when a new page becomes current.
PDFKIT_EXTERN NSNotificationName const PDFViewScaleChangedNotification PDFKIT_AVAILABLE(10_4, 11_0);          // Notification when the scale changes.
PDFKIT_EXTERN NSNotificationName const PDFViewAnnotationHitNotification PDFKIT_AVAILABLE(10_4, 11_0);         // Notification when the user clicks on an annotation.
PDFKIT_EXTERN NSNotificationName const PDFViewCopyPermissionNotification PDFKIT_AVAILABLE(10_4, 11_0);        // Notification when the user is denied copy (permissions).
PDFKIT_EXTERN NSNotificationName const PDFViewPrintPermissionNotification PDFKIT_AVAILABLE(10_4, 11_0);       // Notification when the user is denied print (permissions).
PDFKIT_EXTERN NSNotificationName const PDFViewAnnotationWillHitNotification PDFKIT_AVAILABLE(10_4, 11_0);     // Notification before user clicks on an annotation.
PDFKIT_EXTERN NSNotificationName const PDFViewSelectionChangedNotification PDFKIT_AVAILABLE(10_4, 11_0);      // Notification when the current selection has changed.
PDFKIT_EXTERN NSNotificationName const PDFViewDisplayModeChangedNotification PDFKIT_AVAILABLE(10_4, 11_0);    // Notification when the display mode has changed.
PDFKIT_EXTERN NSNotificationName const PDFViewDisplayBoxChangedNotification PDFKIT_AVAILABLE(10_4, 11_0);     // Notification when the display box has changed.
PDFKIT_EXTERN NSNotificationName const PDFViewVisiblePagesChangedNotification PDFKIT_AVAILABLE(10_4, 11_0);   // Notification when the scroll view has scrolled into the bounds of a new page.

PDFKIT_CLASS_AVAILABLE(10_4, 11_0)
@interface PDFView : PDFKitPlatformView
    < UIGestureRecognizerDelegate >
{
@private
    PDFViewPrivate *_private;
}

// -------- document

// Methods for associating a PDFDocument with a PDFView.
@property (nonatomic, retain, nullable) PDFDocument *document;

// -------- page navigation

// Simple page navigation methods.
@property (nonatomic, readonly) BOOL canGoToFirstPage;
- (IBAction)goToFirstPage:(nullable id)sender;

@property (nonatomic, readonly) BOOL canGoToLastPage;
- (IBAction)goToLastPage:(nullable id)sender;

@property (nonatomic, readonly) BOOL canGoToNextPage;
- (IBAction)goToNextPage:(nullable id)sender;

@property (nonatomic, readonly) BOOL canGoToPreviousPage;
- (IBAction)goToPreviousPage:(nullable id)sender;

// Page visitations done via goToFirstPage:, goToLastPage:, goToPage:, etc. methods are recorded with visitation history
// and can be revisited by executing goBack: or goForward:, much like a web browser. Note that visitiation history
// also includes all rect, destination, and selection goTo*: methods.
@property (nonatomic, readonly) BOOL canGoBack;
- (IBAction)goBack:(nullable id)sender;

@property (nonatomic, readonly) BOOL canGoForward;
- (IBAction)goForward:(nullable id)sender;

// Returns the current page you are on. For two-up modes, it is the left page (if there are two). For continuous modes, 
// it finds the page crossing a horizontal line halfway between the views top and bottom bounds.
@property (nonatomic, readonly, nullable) PDFPage *currentPage;

// Scrolls to page.
- (void)goToPage:(PDFPage *)page;

// Returns a PDFDestination representing the current page and point displayed (see -[currentPage] for more comments).
@property (nonatomic, readonly, nullable) PDFDestination *currentDestination;

// Goes to the specified destination.
- (void)goToDestination:(PDFDestination *)destination;

// Goes to the specified selection (since selections can be large, goes to the first character of the selection).
- (void)goToSelection:(PDFSelection *)selection;

// Goes to the specified rectangle on the specified page. If already visible, does nothing. This allows you to scroll 
// the PDFView to a specific PDFAnnotation or PDFSelection (since both object have bounds methods).
// Note: rect is specified in page coordinates. Example: You might use this function when tabbing through a form to keep
// focus on the active element.
- (void)goToRect:(PDFRect)rect onPage:(PDFPage *)page;

// -------- display mode

// See PDFDisplayMode constants above. Default is kPDFDisplaySinglePageContinuous.
@property (nonatomic) PDFDisplayMode displayMode;

// Set the layout direction, either vertical or horizontal, for the given display mode
// Defaults to vertical layout (kPDFDisplayDirectionVertical).
@property (nonatomic) PDFDisplayDirection displayDirection PDFKIT_AVAILABLE(10_13, 11_0);

// Toggle displaying or not displaying page breaks (spacing) between pages. This spacing value
// is defined by the pageBreakMargins property. If displaysPageBreaks is NO, then pageBreakMargins
// will always return { 0.0, 0.0, 0.0, 0.0 }
@property (nonatomic) BOOL displaysPageBreaks;

// If displaysPageBreaks is enabled, you may customize the spacing between pages by defining margins for
// the top, bottom, left, and right of each page. Note that pageBreakMargins only allows positive values
// and will clamp any negative value to 0.0. By default, if displaysPageBreaks is enabled, pageBreakMargins
// is { 4.75, 4.0, 4.75, 4.0 } (with respect to top, left, bottom, right), otherwise it is { 0.0, 0.0, 0.0, 0.0 }
@property (nonatomic) PDFEdgeInsets pageBreakMargins PDFKIT_AVAILABLE(10_13, 11_0);

// Specifies the box to display/clip to. Default is kPDFDisplayBoxCropBox.
@property (nonatomic) PDFDisplayBox displayBox;

// Specifies whether the first page is to be treated as a cover and (for two-up modes) displayed by itself.
@property (nonatomic) BOOL displaysAsBook;

// Specifies presentation of pages from right-to-left. Defaults to NO.
@property (nonatomic) BOOL displaysRTL PDFKIT_AVAILABLE(10_13, 11_0);

// Default is a 50% gray.
@property (nonatomic, strong) PDFKitPlatformColor *backgroundColor;

// Allows setting the interpolation quality for images drawn into the PDFView context. 
@property (nonatomic) PDFInterpolationQuality interpolationQuality PDFKIT_AVAILABLE(10_7, 11_0);


// Changes the underlying scroll view to use a UIPageViewController as a way to layout and navigate
// pages. Note that you can change the orientation via -[PDFView setDisplayDirection:], and that
// the property -[PDFView displayMode] is ignored: layout is always assumed single page continuous.
// The viewOptions argument is given to the UIPageViewController initializer, as a way to pass in page spacing, etc.
- (void)usePageViewController:(BOOL)enable withViewOptions:(nullable NSDictionary*)viewOptions PDFKIT_AVAILABLE(NA, 11_0);
@property (nonatomic, readonly) BOOL isUsingPageViewController PDFKIT_AVAILABLE(NA, 11_0);


// -------- delegate

@property (nonatomic, weak, nullable) id< PDFViewDelegate > delegate;

// -------- scaling

// Method to get / set the current scaling on the displayed PDF document. Default is 1.0 (actual size).
// Note that the given scaleFactor is clamped by the current min / max scale factors.
// When using a page view controller layout on iOS, this only affects the currently visible page and
// is ignored for any future loaded pages. You can observe the PDFViewPageChangedNotification notification
// to see when new pages are visible to apply new scale factors to them.
@property (nonatomic) CGFloat scaleFactor;

// Set the minimum and maximum scaling factors for the PDF document. Assigning these values will implicitly turn
// off autoScales, and allows scaleFactor to vary between these min / max scale factors
@property (nonatomic) CGFloat minScaleFactor PDFKIT_AVAILABLE(10_13, 11_0);
@property (nonatomic) CGFloat maxScaleFactor PDFKIT_AVAILABLE(10_13, 11_0);

// Toggles mode whereby the scale factor is automatically changed as the view is resized, or rotated, to maximize the
// PDF displayed. For continuous modes this is a "fit width" behavior, for non-continuous modes it is a "best fit" behavior.
@property (nonatomic) BOOL autoScales;

// Regardless of current autoScales mode, this returns the "size to fit" scale factor that autoScales would use
// for scaling the current document and layout. For continuous modes this is a "fit width" scale, for
// non-continuous modes it is a "best fit" scale.
@property (nonatomic, readonly) CGFloat scaleFactorForSizeToFit PDFKIT_AVAILABLE(10_13, 11_0);

// Zooming changes the scaling by root-2.
- (IBAction)zoomIn:(nullable id)sender;
@property (nonatomic, readonly) BOOL canZoomIn;

- (IBAction)zoomOut:(nullable id)sender;
@property (nonatomic, readonly) BOOL canZoomOut;

// -------- events

// Returns type of area (see defines above) mouse is over. This method is useful for subclasses.
- (PDFAreaOfInterest)areaOfInterestForMouse:(PDFKitPlatformEvent *)event;
- (PDFAreaOfInterest)areaOfInterestForPoint:(PDFPoint)cursorLocation;


// Performs the action specified by action.
- (void)performAction:(PDFAction *)action PDFKIT_AVAILABLE(10_5, 11_0);

// -------- selection

// Getter: Returns actual instance of the current PDFSelection object. If you wish to modify this, you should make a copy of
// the selection returned and modify that instead. Method may return nil if there is no selection.
// Setter: Set current selection to selection. The view will redraw as necessary. The view will not scroll.
// Call -[scrollSelectionToVisible:] to scroll to the current selection.
@property (nonatomic, strong, nullable) PDFSelection *currentSelection;

// Like -[setCurrentSelection:] above but with the additional parameter that specifies whether setting the selection
// should be animated. The animation draws the user's attention to the new selection. Useful when searching.
- (void)setCurrentSelection:(nullable PDFSelection *)selection animate:(BOOL)animate PDFKIT_AVAILABLE(10_5, 11_0);

// Equivalent to -[PDFView setCurrentSelection: nil].
- (void)clearSelection;

// Select all text for the entire document, unless in in page view controller mode for iOS,
// where only the current page is selected.
- (IBAction)selectAll:(nullable id)sender;

// If the selection is not visible, scrolls view so that it is.
- (IBAction)scrollSelectionToVisible:(nullable id)sender;

// The following calls allow you to associate an array of PDFSelections with a PDFView. Unlike the user selection 
// (above), these selections do not go away when the user clicks in the PDFView, etc. You must explicitly remove them 
// by passing nil to -[setHighlightedSelections:]. These methods allow you to highlight text perhaps to indicate 
// matches from a text search. To avoid confusion you should probably make sure the PDFSelections passed in are a 
// different color from the user's default text selection color. Commonly used for highlighting search results.
@property (nonatomic, copy, nullable) NSArray<PDFSelection*> *highlightedSelections PDFKIT_AVAILABLE(10_5, 11_0);

// -------- rendering

// Context-aware subclassing functions

// For subclasses. This method is called for each visible page requiring rendering. By subclassing you can draw on top
// of the PDF page or draw the page entirely yourself. Default implementation erases page to white and calls:
// [page drawWithBox: [self displayBox] toContext: context]. Note that this may be called multiple times for
// the same page due to tiling of renderable content.
- (void)drawPage:(PDFPage *)page toContext:(CGContextRef)context PDFKIT_AVAILABLE(10_12, 11_0);

// Also a handy method for sub-classing. Called for post-page rendering. In this method however no scaling/rotating is
// applied to the current context to map to page-space. The context is in "view-space" coordinates.
- (void)drawPagePost:(PDFPage *)page toContext:(CGContextRef)context PDFKIT_AVAILABLE(10_12, 11_0);


// -------- pasteboard

// Copy the selection (if any) to the pasteboard.
- (IBAction)copy:(nullable id)sender;


// -------- conversion

// Given a point in view coordinates, returns the page at that point. May return nil if no page at point and nearest is NO.
- (nullable PDFPage *)pageForPoint:(PDFPoint)point nearest:(BOOL)nearest;

// Converts a point from view coordinates to page coordinates.
- (PDFPoint)convertPoint:(PDFPoint)point toPage:(PDFPage *)page;

// Converts a rect from view coordinates to page coordinates.
- (PDFRect)convertRect:(PDFRect)rect toPage:(PDFPage *)page;

// Converts a point from page coordinates to view coordinates.
- (PDFPoint)convertPoint:(PDFPoint)point fromPage:(PDFPage *)page;

// Converts a rect from page coordinates to view coordinates.
- (PDFRect)convertRect:(PDFRect)rect fromPage:(PDFPage *)page;

// -------- misc

// Returns the innermost view used by PDFView. This is the view representing the displayed document pages.
@property (nonatomic, readonly, nullable) PDFKitPlatformView *documentView;

// Tells PDFView to calculate (layout) the inner views. Called automatically when -[setDocument] and -[setDisplayBox]
// are called. You'll need to call this if you add or remove a page on the document, rotate a page etc.
- (void)layoutDocumentView;

// Tells PDFView that an annotation has changed on the specified page. PDFView re-scans then for tooltips, popups, 
// and informs PDFThumbnailViews so the thumbnail can be redrawn. 
- (void)annotationsChangedOnPage:(PDFPage *)page PDFKIT_AVAILABLE(10_5, 11_0);

// Handy for initially sizing PDFView. Returns the size needed to display the 'row' of the view's current document
// containing the specified page at the current scale factor and with the current display attributes.
- (PDFSize)rowSizeForPage:(PDFPage *)page;


// Returns an array of PDFPage objects representing the currently visible pages. May return empty array if no document is assigned.
@property (nonatomic, readonly) NSArray<PDFPage *> *visiblePages PDFKIT_AVAILABLE(10_5, 11_0);

// Turns on or off data detection. If enabled, page text will be scanned for URL's as the page becomes visible. Where
// URL's are found, Link annotations are created in place. These are temporary annotations and are not saved.
@property (nonatomic) BOOL enableDataDetectors PDFKIT_AVAILABLE(10_6, 11_0);

@end

@protocol PDFViewDelegate< NSObject >
@optional

// Delegates implementing the following method will be called to handle clicks on URL links within the PDFView. The
// default implementation calls [[NSWorkspace sharedWorkspace] openURL: url].
- (void)PDFViewWillClickOnLink:(PDFView *)sender withURL:(NSURL *)url PDFKIT_AVAILABLE(10_5, 11_0);


// Certain PDFAction's may request that the PDF viewer application perform a Find. Delegates responding to the below
// method will be called when the user clicks on an annotation with such an action.
- (void)PDFViewPerformFind:(PDFView *)sender PDFKIT_AVAILABLE(10_5, 11_0);

// Certain PDFAction's may request that the PDF viewer application bring up a panel allowing the user to enter a 
// specific page number. Delegates responding to the below method will be called when the user clicks on an annotation
// with such an action.
- (void)PDFViewPerformGoToPage:(PDFView *)sender PDFKIT_AVAILABLE(10_5, 11_0);

// Delegates implementing the following method will be called to handle clicks on annotations containing a 
// PDFActionRemoteGoTo action. The action contains a URL and a page index and point. The delegate should open the PDF 
// indicated by the URL and go to the page and point indicated. The easiest way to do the latter is to create a 
// PDFDestination with the page index and point once a PDFDocument from the URL is created - then you can call:
// -[PDFView goToDestination:]. The default implementation simply beeps.
- (void)PDFViewOpenPDF:(PDFView *)sender forRemoteGoToAction:(PDFActionRemoteGoTo *)action PDFKIT_AVAILABLE(10_5, 11_0);

@end


NS_ASSUME_NONNULL_END
// ==========  PDFKit.framework/Headers/PDFAnnotationUtilities.h
//
//  PDFAnnotationUtilities.h
//  Copyright © 2016 Apple. All rights reserved.
//
//  This file includes several helper functions that match legacy PDFAnnotation
//  subclass functions, helping simplify creating properties for common annotations.
//

#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFAnnotation.h>

NS_ASSUME_NONNULL_BEGIN

// Style used for line end caps.
typedef NS_ENUM(NSInteger, PDFLineStyle)
{
    kPDFLineStyleNone = 0,
    kPDFLineStyleSquare = 1,
    kPDFLineStyleCircle = 2,
    kPDFLineStyleDiamond = 3,
    kPDFLineStyleOpenArrow = 4,
    kPDFLineStyleClosedArrow = 5
};

// Icon that appears indicating text annotation pop-up.
typedef NS_ENUM(NSInteger, PDFTextAnnotationIconType)
{
    kPDFTextAnnotationIconComment = 0,
    kPDFTextAnnotationIconKey = 1,
    kPDFTextAnnotationIconNote = 2,
    kPDFTextAnnotationIconHelp = 3,
    kPDFTextAnnotationIconNewParagraph = 4,
    kPDFTextAnnotationIconParagraph = 5,
    kPDFTextAnnotationIconInsert = 6
};

// Types of markup annotations.
typedef NS_ENUM(NSInteger, PDFMarkupType)
{
    kPDFMarkupTypeHighlight = 0,
    kPDFMarkupTypeStrikeOut = 1,
    kPDFMarkupTypeUnderline = 2
};

// Type of control.
typedef NS_ENUM(NSInteger, PDFWidgetControlType)
{
    kPDFWidgetUnknownControl = -1,
    kPDFWidgetPushButtonControl = 0,
    kPDFWidgetRadioButtonControl = 1,
    kPDFWidgetCheckBoxControl = 2
};

// Cell state.
typedef NS_ENUM(NSInteger, PDFWidgetCellState)
{
    kPDFWidgetMixedState = -1,
    kPDFWidgetOffState = 0,
    kPDFWidgetOnState = 1,
};

// All PDF annotation subtypes that PDFKit can render: based on Adobe PDF specification, Table 8.20: Annotation types.
// Annotation subtypes not supported: Polygon, PolyLine, Squiggly, Caret, Caret, FileAttachment,
// Sound, Movie, Screen, PrinterMark, TrapNet, Watermark, 3D, Rect.
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeText PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeLink PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeFreeText PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeLine PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeSquare PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeCircle PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeHighlight PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeUnderline PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeStrikeOut PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeInk PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeStamp PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypePopup PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeWidget PDFKIT_AVAILABLE(10_13, 11_0);

// Widget annotations have the following possible subtypes: Button, Choice, Signature, and Text
typedef NSString* const PDFAnnotationWidgetSubtype NS_STRING_ENUM;

PDFKIT_EXTERN PDFAnnotationWidgetSubtype PDFAnnotationWidgetSubtypeButton PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationWidgetSubtype PDFAnnotationWidgetSubtypeChoice PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationWidgetSubtype PDFAnnotationWidgetSubtypeSignature PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationWidgetSubtype PDFAnnotationWidgetSubtypeText PDFKIT_AVAILABLE(10_13, 11_0);

// Line annotation have the following line ending types (this maps directly to PDFLineStyle)
typedef NSString* const PDFAnnotationLineEndingStyle NS_STRING_ENUM;

PDFKIT_EXTERN PDFAnnotationLineEndingStyle PDFAnnotationLineEndingStyleNone PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationLineEndingStyle PDFAnnotationLineEndingStyleSquare PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationLineEndingStyle PDFAnnotationLineEndingStyleCircle PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationLineEndingStyle PDFAnnotationLineEndingStyleDiamond PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationLineEndingStyle PDFAnnotationLineEndingStyleOpenArrow PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationLineEndingStyle PDFAnnotationLineEndingStyleClosedArrow PDFKIT_AVAILABLE(10_13, 11_0);

// Text annotations have the following icon types:
typedef NSString* const PDFAnnotationTextIconType NS_STRING_ENUM;

PDFKIT_EXTERN PDFAnnotationTextIconType PDFAnnotationTextIconTypeComment PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationTextIconType PDFAnnotationTextIconTypeKey PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationTextIconType PDFAnnotationTextIconTypeNote PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationTextIconType PDFAnnotationTextIconTypeHelp PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationTextIconType PDFAnnotationTextIconTypeNewParagraph PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationTextIconType PDFAnnotationTextIconTypeParagraph PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationTextIconType PDFAnnotationTextIconTypeInsert PDFKIT_AVAILABLE(10_13, 11_0);

// Highlighting styles
typedef NSString* const PDFAnnotationHighlightingMode NS_STRING_ENUM;

PDFKIT_EXTERN PDFAnnotationHighlightingMode PDFAnnotationHighlightingModeNone PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationHighlightingMode PDFAnnotationHighlightingModeInvert PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationHighlightingMode PDFAnnotationHighlightingModeOutline PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationHighlightingMode PDFAnnotationHighlightingModePush PDFKIT_AVAILABLE(10_13, 11_0);

@class PDFDestination;

// Helper functions for directly manipulating annotation dictionaries
@interface PDFAnnotation (PDFAnnotationUtilities)

// Font and font color associated with the text field.
// Used by annotations type(s): /FreeText, /Popup, /Widget (field type(s): /Btn, /Ch, and /Tx).
@property (nonatomic, copy, nullable) PDFKitPlatformFont *font;

// Width of line used to stroke border.
// Used by annotations type(s): /FreeText, /Widget (field type(s): /Btn, /Ch, and /Tx).
@property (nonatomic, copy, nullable) PDFKitPlatformColor *fontColor;

// Alignment of text within annotation bounds.  Supported: NSLeftTextAlignment, NSRightTextAlignment and
// NSCenterTextAlignment.
// Used by annotations type(s): /FreeText, /Widget (field type(s): /Tx).
@property (nonatomic) NSTextAlignment alignment;

// Points specifying start and end points for line annotation (required).
// Points are specified in annotation space.
// Used by annotations type(s): /Line.
@property (nonatomic) PDFPoint startPoint;
@property (nonatomic) PDFPoint endPoint;

// Style used for ornaments at the lines start and end (optional, PDF 1.4).
// Used by annotations type(s): /Line.
@property (nonatomic) PDFLineStyle startLineStyle;
@property (nonatomic) PDFLineStyle endLineStyle;

// Class methods to help with mapping PDFLineStyle to the associated name based on PDF specification
// Used by annotations type(s): /Line.
+ (PDFLineStyle) lineStyleFromName:(NSString *)name;
+ (NSString *) nameForLineStyle:(PDFLineStyle)style;

// The type of icon displayed in the PDF.  Supported icons: "Comment", "Key", "Note", "Help", "NewParagraph",
// "Paragraph" and "Insert".
// Used by annotations type(s): /Text.
@property (nonatomic) PDFTextAnnotationIconType iconType;

// Array of n * 4 points, packed as NSValue pointValue / CGPointValue, defining n quadrilaterals in page space where n is the number of quad points.
// The points for each quad are ordered in a 'Z' pattern. That is, the first point should represent the upper left
// point representing the start of the marked-up text, the next point will be the upper right, the third point will
// represent the lower left of the text and the last point the lower right.
// Points are specified relative to the annotation's bound's origin.
@property (nonatomic, copy, nullable) NSArray<NSValue *> *quadrilateralPoints;

// Type of mark-up (highlight, strike-out or underline). Changing the markup type also changes the annotations type.
// Used by annotations type(s): /Highlight, /StrikeOut, /Underline.
@property (nonatomic) PDFMarkupType markupType;

// The specific field type of a widget annotation (button, choice, or text).
// Used by annotations type(s): /Widget (field type(s): /Btn, /Ch, /Tx).
@property (nonatomic, copy) PDFAnnotationWidgetSubtype widgetFieldType;

// The type of button widget control type (radio button, push button, or checkbox).
// Used by annotations type(s): /Widget (field type(s): /Btn).
@property (nonatomic) PDFWidgetControlType widgetControlType;

// Used to configure multiline PDF text fields.
// Used by annotations type(s): /Widget (field type(s): /Tx).
@property (nonatomic, getter=isMultiline) BOOL multiline;

// Used to determine if a PDF text field is a password field.
// Used by annotations type(s): /Widget (field type(s): /Tx).
@property (nonatomic, readonly) BOOL isPasswordField;

// Used to configure combing for PDF text fields.
// If set, the field is automatically divided into as many equally spaced positions, or combs, as the value of the
// maximum length of the field. To get the maximum length, use annotaiton key: PDFAnnotationKeyWidgetMaxLen.
// Used by annotations type(s): /Widget (field type(s): /Tx).
@property (nonatomic, getter=hasComb) BOOL comb;

// Maximum characters allowed (optional, zero indicates no specified maximum).
// Used by annotations type(s): /Widget (field type(s): /Tx).
@property (nonatomic) NSInteger maximumLength;

// The string value for a widget annotation.
// Used by annotations type(s): /Widget (field type(s): /Btn, /Ch, /Tx).
@property (nonatomic, copy, nullable) NSString *widgetStringValue;

// The string value for a widget annotation.
// Used by annotations type(s): /Widget (field type(s): /Btn, /Ch, /Tx).
@property (nonatomic, copy, nullable) NSString *widgetDefaultStringValue;

// For radio buttons, indicates whether clicking on widget whose state is already On toggles it Off.
// Used by annotations type(s): /Widget (field type(s): /Btn).
@property (nonatomic) BOOL allowsToggleToOff;

// For radio buttons, indicates whether a group of radio buttons will turn on and off in
// unison; that is if one is checked, they are all checked. If clear, the buttons are mutually exclusive.
// Used by annotations type(s): /Widget (field type(s): /Btn).
@property (nonatomic) BOOL radiosInUnison;

// Determines if a text field should be editable or not.
// Used by annotations type(s): /Widget (field type(s): /Tx).
@property (nonatomic, getter=isReadOnly) BOOL readOnly;

// There are two flavors of Choice widget annotations, lists and pop-up menus. This method allow you to differentiate.
// Used by annotations type(s): /Widget (field type(s): /Ch).
@property (nonatomic, getter=isListChoice) BOOL listChoice;

// The choices are an array of strings indicating the options (items) in either a list or pop-up menu.
// Used by annotations type(s): /Widget (field type(s): /Ch).
@property (nonatomic, copy, nullable) NSArray<NSString *> *choices;

// The choices are an array of strings indicating the  option’s export values in either a list or pop-up menu.
// Used by annotations type(s): /Widget (field type(s): /Ch).
@property (nonatomic, copy, nullable) NSArray<NSString *> *values;

// The current state of a button widget annotation.
// Used by annotations type(s): /Widget (field type(s): /Btn).
@property (nonatomic) PDFWidgetCellState buttonWidgetState;

// The string that represents the ON state of a button widget annotation.
// This should be set when trying to, for example, group together a set of radio buttons with the same field name.
// When buttons share the same field name, their individual state strings set them apart from one another.
// Used by annotations type(s): /Widget (field type(s): /Btn).
@property (nonatomic, copy) NSString *buttonWidgetStateString;

// Used to tell if an annotation is open or closed.
// Used by annotations type(s): /Popup.
@property (nonatomic, getter=isOpen) BOOL open;

// Array of NSBezierPaths / UIBezierPaths that comprise the annotation.
// Paths are specified in annotation space.
// Used by annotations type(s): /Ink.
@property (nonatomic, readonly, nullable) NSArray<PDFKitPlatformBezierPath *> *paths;

// Add or remove paths from the annotation.
// Path points are specified in annotation space.
// Used by annotations type(s): /Ink.
- (void)addBezierPath:(PDFKitPlatformBezierPath *)path;
- (void)removeBezierPath:(PDFKitPlatformBezierPath *)path;

// Destination for the link. May be nil if no destination associated with link; in this case the -[URL] may be valid.
// The preferred way though is to call -[PDFAnnotation action] and -[PDFAnnotation setAction:].
// Used by annotations type(s): /Link.
@property (nonatomic, strong, nullable) PDFDestination *destination;

// URL for the link. May be nil if no URL action associated with link; in this case the -[destination] may be valid.
// The preferred way though is to call -[PDFAnnotation action] and -[PDFAnnotation setAction:].
// Used by annotations type(s): /Link.
@property (nonatomic, copy, nullable) NSURL *URL;

// Widget annotations backed by form data have (internal) field names with which to associate a value or data.
// Can also be used for ResetForm actions.
// Used by annotations type(s): /Widget (field type(s): /Btn, /Ch, /Tx).
@property (nonatomic, copy, nullable) NSString *fieldName;

// Label for the button. Applies to kPDFWidgetPushButtonControl only.
// Used by annotations type(s): /Widget (field type(s): /Btn).
@property (nonatomic, copy, nullable) NSString *caption;

// Background color characteristics.
// Used by annotations type(s): /Widget (field type(s): /Btn, /Ch, /Tx).
@property (nonatomic, copy, nullable) PDFKitPlatformColor *backgroundColor;

@end

NS_ASSUME_NONNULL_END
// ==========  PDFKit.framework/Headers/PDFPage.h
//
//  PDFPage.h
//  Copyright © 2016 Apple. All rights reserved.
//
//  PDFPage is a logical representation of a PDF document's page. Typically pages are
//  retrieved from a PDFDocument, though they can be constructed from scratch via either
//  init method or initWithImage:. Pages can have their drawing methods overridden to allow
//  custom drawing. Pages own a set of annotations, and have the ability to add, mutate, or
//  remove them. Pages also expose text-selection methods, driven in page-space positions.
//

#import <PDFKit/PDFKitPlatform.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFDocument, PDFAnnotation, PDFSelection, PDFPagePrivate, PDFAccessibilityNode;

// Page boxes.
PDFKIT_ENUM_AVAILABLE(10_4, 11_0)
typedef NS_ENUM(NSInteger, PDFDisplayBox)
{
    kPDFDisplayBoxMediaBox = 0, 
    kPDFDisplayBoxCropBox = 1, 
    kPDFDisplayBoxBleedBox = 2, 
    kPDFDisplayBoxTrimBox = 3, 
    kPDFDisplayBoxArtBox = 4
};

PDFKIT_CLASS_AVAILABLE(10_4, 11_0)
@interface PDFPage : NSObject <NSCopying>
{
@private
	PDFPagePrivate *_private;
}

// -------- initializer

// For subclassers, just call the standard -(id) init.
// Note: -[PDFPage init] creates a new empty page with a media box set to (0.0, 0.0), [612.0, 792.0].
- (instancetype)init NS_DESIGNATED_INITIALIZER;

// Returns a PDFPage for the passed in image. An easy way to create a PDFPage from an image to add to a PDFDocument.
- (nullable instancetype)initWithImage:(PDFKitPlatformImage *)image PDFKIT_AVAILABLE(10_5, 11_0) NS_DESIGNATED_INITIALIZER;

// -------- accessors

// The PDFDocument the page is associated with.
@property (nonatomic, readonly, weak, nullable) PDFDocument *document;

// This is the CGPDFPage associated with the PDFPage object. With this object you can call many CoreGraphics API methods.
// May return NULL if the owning document was not created from an existing PDF file or data or if the page itself was 
// created independently.
@property (nonatomic, readonly, nullable) CGPDFPageRef pageRef;

// The page label. Usually "1" for the first page, "2" for the second, etc.
@property (nonatomic, readonly, nullable) NSString *label;

// The bounds for the specified box (see defines above). Only the media box is required for a PDF. If the crop box is
// requested and not present in the PDF, the media box is returned. If other boxes are requested and not present, the 
// value for the crop box is returned. Throws a range exception if box is not in range. Coordinates for the box are in 
// page space - you may need to transform the points if the page has a rotation on it. Also, note that the bounds 
// returned are intersected with the page's media box.
- (PDFRect)boundsForBox:(PDFDisplayBox)box;

// Set bounds for the specified box. If the specified box did not previously exist, it will now. To remove a box pass 
// NSZeroRect for the bounds (you cannot however remove the media box). Throws a range exception if box is not in range.
- (void)setBounds:(PDFRect)bounds forBox:(PDFDisplayBox)box;

// Rotation on a page. Must be 0, 90, 180 or 270 (negative rotations will be "normalized" to one of 0, 90, 180 or 270).
// Some PDF's have an inherent rotation and so -[rotation] may be non-zero when a PDF is first opened.
@property (nonatomic) NSInteger rotation;

// -------- annotations

// Array of all PDFAnnotation objects on this page.
@property (nonatomic, readonly) NSArray<PDFAnnotation*> *annotations;

// Method to turn on or off the display of annotations when the page is drawn.
@property (nonatomic) BOOL displaysAnnotations;

// Methods allowing annotations to be added or removed.
- (void)addAnnotation:(PDFAnnotation *)annotation;
- (void)removeAnnotation:(PDFAnnotation *)annotation;

// Hit-testing method returns the annotation at point (or NULL if none). The point is in page-space.
- (nullable PDFAnnotation *)annotationAtPoint:(PDFPoint)point;

// -------- rendering

// This transform correctly rotates and offsets based on the given page's rotation property and the display box type.
- (CGAffineTransform)transformForBox:(PDFDisplayBox)box PDFKIT_AVAILABLE(10_12, 11_0);

// Context aware rendering:

// Drawing method takes into account page rotation, draws in page space relative to and clipped to the box bounds. If
// -[displaysAnnotations] is true, also draws any page annotations. Does not clear the background (page white).
- (void)drawWithBox:(PDFDisplayBox)box toContext:(CGContextRef)context PDFKIT_AVAILABLE(10_12, 11_0);

// Given a display box, will transform the given context to take into account the rotation of the page as well as
// the origin of the box with respect to the page's base coordinates system. This is a convenience method to call
// from within -[PDFView drawPage:toContext:] or -[PDFAnnotation drawWithBox:inContext:].
- (void)transformContext:(CGContextRef)context forBox:(PDFDisplayBox)box PDFKIT_AVAILABLE(10_12, 11_0);

// Convenience function that returns an image of this page, with annotations, that fits the given size.
// Note that the produced image is "size to fit": it retains the original page geometry. The size you give
// may not match the size of the returned image, but the returned image is guaranteed to be equal or less.
- (PDFKitPlatformImage *)thumbnailOfSize:(PDFSize)size forBox:(PDFDisplayBox)box PDFKIT_AVAILABLE(10_13, 11_0);

// -------- text

// Number of characters on the page (including linefeeds and spaces inserted).
@property (nonatomic, readonly) NSUInteger numberOfCharacters;

// String (with linefeeds and in some cases spaces inserted) representing the text on the page.
@property (nonatomic, readonly, nullable) NSString *string;
@property (nonatomic, readonly, nullable) NSAttributedString *attributedString;

// Returns the bounds in page-space, of the character at index.
- (PDFRect)characterBoundsAtIndex:(NSInteger)index;

// Returns the index of the character at point (in page space). Returns the index of the first character if multiple characters are at this point.
// Returns NSNotFound if no character at point. Earlier version of PDFKit (prior to Lion) returned -1 if no character at point.
- (NSInteger)characterIndexAtPoint:(PDFPoint)point;

// -------- selections

// Given a rect in page-space, returns a selection representing enclosed text on page.
- (nullable PDFSelection *)selectionForRect:(PDFRect)rect;

// Given a point in page-space, returns a selection representing a whole word at that point. May return NULL if no 
// character (and by extension no word) under point.
- (nullable PDFSelection *)selectionForWordAtPoint:(PDFPoint)point;

// Given a point in page-space, returns a selection representing a whole line at that point. May return NULL if no 
// character (and by extension no line) under point.
- (nullable PDFSelection *)selectionForLineAtPoint:(PDFPoint)point;

// Returns a selection representing text between startPt and endPt. Points are sorted first top to bottom, left to right.
- (nullable PDFSelection *)selectionFromPoint:(PDFPoint)startPoint toPoint:(PDFPoint)endPoint;

// Given a range, returns a selection representing text within that range. Will raise an exception if the range length 
// is zero or if the range is outside the range of the characters on the page.
- (nullable PDFSelection *)selectionForRange:(NSRange)range;

// -------- misc

// Returns PDF data (a proper PDF document) consisting of a single page (this page).
// NOTE: External page links are not preserved.
// NOTE: Versions of PDFKit before SnowLeopard did not return autorelease data for -[dataRepresentation]. You had to 
// release the data yourself. Beginning with apps compiled on SnowLeopard the data returned is autoreleased.
@property (nonatomic, readonly) NSData *dataRepresentation;

@end



NS_ASSUME_NONNULL_END
// ==========  PDFKit.framework/Headers/PDFDocument.h
//
//  PDFDocument.h
//  Copyright © 2016 Apple. All rights reserved.
//
//  PDFDocument is the logical representation of a PDF file. It is a container of PDFPages,
//  giving you the ability to load, modify, and save a set of PDF pages. It also gives you the
//  ability to unlock, search, and interact with the document's structure. You can instantiate
//  a PDFDocument with either the init method, initWithURL:, or initWithData:. Documents
//  that are locked or encrypted must be unlocked before reading or mutating any properties.
//  This is done via "unlockWithPassword:", and on success will return YES and post a
//  PDFDocumentDidUnlockNotification notification. You may search synchronously or asynchronously
//  via the set of "findString:" functions. When searching asynchronously, you will receive
//  periodic updates via search related notifications (See below).
//
//  Note that if you want your instance of a PDFDocument to be backed by a custom PDFPage
//  class, you can do so by register a delegate that overloads the method "classForPage".
//  In doing so, PDFDocument will instantiate your class via the init method.
//

#import <PDFKit/PDFKitPlatform.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFDestination, PDFOutline, PDFPage, PDFSelection, PDFDocumentPrivate;
@protocol PDFDocumentDelegate;


// Document permissions status. For encrypted PDF's, supplying the owner password will enable owner permission status.
PDFKIT_ENUM_AVAILABLE(10_4, 11_0)
typedef NS_ENUM(NSInteger, PDFDocumentPermissions)
{
	kPDFDocumentPermissionsNone = 0, 
	kPDFDocumentPermissionsUser = 1, 
	kPDFDocumentPermissionsOwner = 2
};

// Notifications.
PDFKIT_EXTERN NSNotificationName const PDFDocumentDidUnlockNotification PDFKIT_AVAILABLE(10_4, 11_0);           // The notification object is self.
PDFKIT_EXTERN NSNotificationName const PDFDocumentDidBeginFindNotification PDFKIT_AVAILABLE(10_4, 11_0);        // The notification object is self, no userInfo dictionary.
PDFKIT_EXTERN NSNotificationName const PDFDocumentDidEndFindNotification PDFKIT_AVAILABLE(10_4, 11_0);          // The notification object is self, no userInfo dictionary.
PDFKIT_EXTERN NSNotificationName const PDFDocumentDidBeginPageFindNotification PDFKIT_AVAILABLE(10_4, 11_0);    // The notification object is self, the userInfo dictionary
                                                                                                                //     contains the page index as an NSNumber for the key
                                                                                                                //     @"PDFDocumentPageIndex".
PDFKIT_EXTERN NSNotificationName const PDFDocumentDidEndPageFindNotification PDFKIT_AVAILABLE(10_4, 11_0);      // The notification object is self, the userInfo dictionary
                                                                                                                //     contains the page index as an NSNumber for the key
                                                                                                                //     @"PDFDocumentPageIndex".
PDFKIT_EXTERN NSNotificationName const PDFDocumentDidFindMatchNotification PDFKIT_AVAILABLE(10_4, 11_0);        // The notification object is self, the userInfo dictionary
                                                                                                                //     contains a PDFSelection (found instance) for the key
                                                                                                                //     @"PDFDocumentFoundSelection".
PDFKIT_EXTERN NSNotificationName const PDFDocumentDidBeginWriteNotification PDFKIT_AVAILABLE(10_4, 11_0);       // The notification object is self, no userInfo dictionary.
PDFKIT_EXTERN NSNotificationName const PDFDocumentDidEndWriteNotification PDFKIT_AVAILABLE(10_4, 11_0);         // The notification object is self, no userInfo dictionary.
PDFKIT_EXTERN NSNotificationName const PDFDocumentDidBeginPageWriteNotification PDFKIT_AVAILABLE(10_4, 11_0);   // The notification object is self, the userInfo dictionary
                                                                                                                //     contains the page index as an NSNumber for the key
                                                                                                                //     @"PDFDocumentPageIndex".
PDFKIT_EXTERN NSNotificationName const PDFDocumentDidEndPageWriteNotification PDFKIT_AVAILABLE(10_4, 11_0);     // The notification object is self, the userInfo dictionary
                                                                                                                //     contains the page index as an NSNumber for the key
                                                                                                                //     @"PDFDocumentPageIndex".

// Document attributes (see -[documentAttributes] below).
typedef NSString *PDFDocumentAttribute NS_STRING_ENUM;

PDFKIT_EXTERN PDFDocumentAttribute const PDFDocumentTitleAttribute PDFKIT_AVAILABLE(10_4, 11_0);                // NSString containing document title.
PDFKIT_EXTERN PDFDocumentAttribute const PDFDocumentAuthorAttribute PDFKIT_AVAILABLE(10_4, 11_0);               // NSString containing document author.
PDFKIT_EXTERN PDFDocumentAttribute const PDFDocumentSubjectAttribute PDFKIT_AVAILABLE(10_4, 11_0);              // NSString containing document title.
PDFKIT_EXTERN PDFDocumentAttribute const PDFDocumentCreatorAttribute PDFKIT_AVAILABLE(10_4, 11_0);              // NSString containing name of app that created document.
PDFKIT_EXTERN PDFDocumentAttribute const PDFDocumentProducerAttribute PDFKIT_AVAILABLE(10_4, 11_0);             // NSString containing name of app that produced PDF data.
PDFKIT_EXTERN PDFDocumentAttribute const PDFDocumentCreationDateAttribute PDFKIT_AVAILABLE(10_4, 11_0);         // NSDate representing document creation date.
PDFKIT_EXTERN PDFDocumentAttribute const PDFDocumentModificationDateAttribute PDFKIT_AVAILABLE(10_4, 11_0);     // NSDate representing last document modification date.
PDFKIT_EXTERN PDFDocumentAttribute const PDFDocumentKeywordsAttribute PDFKIT_AVAILABLE(10_4, 11_0);             // NSArray of NSStrings containing document keywords.

// File writing options (see -[writeToFile:withOptions:] or -[writeToURL:withOptions:options] below).
typedef NSString *PDFDocumentWriteOption NS_STRING_ENUM;

PDFKIT_EXTERN PDFDocumentWriteOption const PDFDocumentOwnerPasswordOption PDFKIT_AVAILABLE(10_4, 11_0);         // NSString for the owner's password. Required for encryption.
                                                                                                                // Owners have full privilege over the document.
PDFKIT_EXTERN PDFDocumentWriteOption const PDFDocumentUserPasswordOption PDFKIT_AVAILABLE(10_4, 11_0);          // NSString for the user's password. Optional for encryption.
                                                                                                                // Users can have limited access to modify, print, or write the file.


PDFKIT_CLASS_AVAILABLE(10_4, 11_0)
@interface PDFDocument : NSObject <NSCopying>
{
@private
    PDFDocumentPrivate* _private;
}

// -------- init

// Initializers.
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithURL:(NSURL *)url NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithData:(NSData *)data NS_DESIGNATED_INITIALIZER;

// -------- accessors

// May return NULL if the document was created from NSData.
@property (nonatomic, readonly, nullable) NSURL *documentURL;

// This is the CGPDFDocument associated with the PDFDocument object.  With this object you can call many CoreGraphics 
// API. May return NULL if the document was not created from an existing PDF file or data.
@property (nonatomic, readonly, nullable) CGPDFDocumentRef documentRef;

// Returns a dictionary with PDF metadata. Metadata is optional for PDF's and so some of the keys may be missing or the 
// entire dictionary may be empty.  See attributes above for keys.
@property (nonatomic, copy, nullable) NSDictionary *documentAttributes;

// PDF version of the PDF file (example: major version = 1, minor = 4; PDF v1.4).
@property (nonatomic, readonly) NSInteger majorVersion;
@property (nonatomic, readonly) NSInteger minorVersion;

// Whether the PDF is encrypted. With the right password, a PDF can be unlocked - nonetheless, the PDF still indicates
// that it is encrypted - just no longer locked. Some PDF's may be encrypted but can be unlocked with the empty string. 
// These are unlocked automatically. 
@property (nonatomic, readonly) BOOL isEncrypted;

// See comments above.
@property (nonatomic, readonly) BOOL isLocked;

// Means of passing in a password to unlock encrypted PDF's.  Calling -[unlockWithPassword:] will attempt to unlock the 
// PDF. If successful, a PDFDocumentDidUnlockNotification notification is sent. You cannot "re-lock" a PDF by passing 
// in a bogus password.  Returns YES if the document is now unlocked, NO otherwise ([self isLocked] == NO).
- (BOOL)unlockWithPassword:(NSString *)password;

// Even unlocked, encrypted PDF's may have certain restrictions regarding printing, copying, etc. placed upon them. These
// indicate the current state.
// Based on Adobe PDF Specification (1.7) Table 3.20: User access permissions
@property (nonatomic, readonly) BOOL allowsPrinting PDFKIT_AVAILABLE(10_4, 11_0);                 // Printing the document
@property (nonatomic, readonly) BOOL allowsCopying PDFKIT_AVAILABLE(10_4, 11_0);                  // Extract content (text, images, etc.)
@property (nonatomic, readonly) BOOL allowsDocumentChanges PDFKIT_AVAILABLE(10_13, 11_0);         // Modify the document contents except for page management (document attrubutes)
@property (nonatomic, readonly) BOOL allowsDocumentAssembly PDFKIT_AVAILABLE(10_13, 11_0);        // Page management: insert, delete, and rotate pages
@property (nonatomic, readonly) BOOL allowsContentAccessibility PDFKIT_AVAILABLE(10_13, 11_0);    // Extract content, but only for the purpose of accessibility
@property (nonatomic, readonly) BOOL allowsCommenting PDFKIT_AVAILABLE(10_13, 11_0);              // Create or modify annotations, including form field entries
@property (nonatomic, readonly) BOOL allowsFormFieldEntry PDFKIT_AVAILABLE(10_13, 11_0);          // Modify form field entries, even if allowsCommenting is NO

// Returns the permissions status of the PDF document. You have kPDFDocumentPermissionsNone status for an encrypted 
// document that you have not supplied either a valid user or owner password. For a document with no encryption, you 
// automatically have kPDFDocumentPermissionsOwner status.
@property (nonatomic, readonly) PDFDocumentPermissions permissionsStatus PDFKIT_AVAILABLE(10_6, 11_0);

// Convenience method. Returns a string representing the entire document (each page's string concatenated with line
// feeds between pages).
@property (nonatomic, readonly, nullable) NSString *string;

// If a PDFDocument has a delegate, delegate methods may be called.  See: NSNotificationNames and 
// PDFDocumentDelegate below.
@property (nonatomic, weak, nullable) id<PDFDocumentDelegate> delegate;

// Methods to record the current state of the PDFDocument as data or a file.  Passing a QuartzFilter object in the 
// options dictionary with the key @"QuartzFilter" will allow you to have the filter applied when saving the PDF.
// NOTE: Versions of PDFKit before SnowLeopard did not return autorelease data for -[dataRepresentation]. You had to 
// release the data yourself.  Beginning with apps compiled on SnowLeopard the data returned is autoreleased.
- (nullable NSData *)dataRepresentation;
- (nullable NSData *)dataRepresentationWithOptions:(NSDictionary *)options PDFKIT_AVAILABLE(10_6, 11_0);

// -[writeToFile:withOptions:] and -[writeToURL:withOptions:] methods may take any CoreGraphics options that are typically
// passed into CGPDFContextCreate(...) and CGPDFContextCreateWithURL(...)'s auxiliaryInfo dictionary. For encryption, you
// may provide an owner and user password via the keys PDFDocumentWriteOption, where the values should be non-zero length
// strings.
- (BOOL)writeToFile:(NSString *)path;
- (BOOL)writeToFile:(NSString *)path withOptions:(nullable NSDictionary<PDFDocumentWriteOption, id> *)options;
- (BOOL)writeToURL:(NSURL *)url;
- (BOOL)writeToURL:(NSURL *)url withOptions:(nullable NSDictionary<PDFDocumentWriteOption, id> *)options;

// -------- outline

// Allows you specify a PDFOutline as the root outline item for this document.  When the PDF is saved the outline tree
// structure is written out to the destination PDF file. Passing NULL is a way to strip any outline from a document.
// Returns the root outline object for the PDF (or NULL if none).
@property (nonatomic, strong, nullable) PDFOutline *outlineRoot PDFKIT_AVAILABLE(10_6, 11_0);

// Given a PDFSelection, this method returns the child outline item the selection most closely falls beneath. Since a
// selection may span multiple outline items, only the point representing the first character of the PDFSelection is 
// considered. Typically, outlines indicate things like chapters for the PDF. Therefore, this method would help you
// identify the chapter the selection falls within.
- (nullable PDFOutline *)outlineItemForSelection:(PDFSelection *)selection;

// -------- pages

// The number of pages in the document.
@property (nonatomic, readonly) NSUInteger pageCount;

// Returns a PDFPage object representing the page at index. Will raise an exception if index is out of bounds. Indices
// are zero-based.
- (nullable PDFPage *)pageAtIndex:(NSUInteger)index;

// Given a PDFPage, returns the pages index within the document. Indices are zero-based.
- (NSUInteger)indexForPage:(PDFPage *)page;

// Methods allowing pages to be inserted, removed, and re-ordered. Can throw range exceptions.
// Note: when inserting a PDFPage, you have to be careful if that page came from another PDFDocument. PDFPage's have a 
// notion of a single document that owns them and when you call the methods below the PDFPage passed in is assigned a 
// new owning document.  You'll want to call -[PDFPage copy] first then and pass this copy to the blow methods. This 
// allows the orignal PDFPage to maintain its original document.
- (void)insertPage:(PDFPage *)page atIndex:(NSUInteger)index;
- (void)removePageAtIndex:(NSUInteger)index;
- (void)exchangePageAtIndex:(NSUInteger)indexA withPageAtIndex:(NSUInteger)indexB;

// This is the class that will be allocated and initialized when page objects are created for the document.  The 
// default implementation returns [PDFPage class] but if you want PDFDocument to use your own custom class you can 
// subclass PDFDocument and implement this method to return your own custom class.  Your class should be a subclass of 
// PDFPage (otherwise the behavior is undefined).
@property (nonatomic, readonly) Class pageClass;

// -------- find

// Searches entire document for string and returns an array of PDFSelections representing all instances found. May 
// return an empty array (if not found). Supported options are: NSCaseInsensitiveSearch, NSLiteralSearch, and 
// NSBackwardsSearch.
- (NSArray<PDFSelection*>*)findString:(NSString *)string withOptions:(NSStringCompareOptions)options;

// Begins a find, searching the document for string.  Search results are handled via a 
// PDFDocumentDidFindMatchNotification or if the delegate implements -[didMatchString:]. Supported options are: 
// NSCaseInsensitiveSearch, NSLiteralSearch, and NSBackwardsSearch.
- (void)beginFindString:(NSString *)string withOptions:(NSStringCompareOptions)options;

// Like -[beginFindString:withOptions:] above but it accepts an array of strings to search for.
// All other comments for -[beginFindString:withOptions:] above apply.
- (void)beginFindStrings:(NSArray<NSString*>*)strings withOptions:(NSStringCompareOptions)options PDFKIT_AVAILABLE(10_5, 11_0);

// Searches for only the next instance of string beginning after the last character of selection with options (or 
// preceding the first character of the selection if NSBackwardsSearch is specified as a search option).
// Returns next instance as a PDFSelection or NULL if the end of the document is reached. Supported options are: 
// NSCaseInsensitiveSearch, NSLiteralSearch, and NSBackwardsSearch. Passing in NULL for selection will start the 
// search from the beginning of the document (or end if NSBackwardsSearch is specified).
- (nullable PDFSelection *)findString:(NSString *)string fromSelection:(nullable PDFSelection *)selection withOptions:(NSStringCompareOptions)options;

// Returns YES if document is currently searching for a string.
@property (nonatomic, readonly) BOOL isFinding;

// Method to cancel a search.  Can be called from a user method being serviced by a find notification.
- (void)cancelFindString;


// -------- selections

// Returns a selection representing text for the entire document.
@property (nonatomic, readonly, nullable) PDFSelection *selectionForEntireDocument;

// Returns a selection representing text from page startPage and point startPt to page endPage and to point endPt on 
// that page. Points are in page-space and relative to their respective pages.  Start and end page can be the same 
// (and are then equivalent to calling -[PDFPage selectionFromPoint: toPoint:]).
- (nullable PDFSelection *)selectionFromPage:(PDFPage *)startPage atPoint:(PDFPoint)startPoint toPage:(PDFPage *)endPage atPoint:(PDFPoint)endPoint;

// Similar to the above method but allows you to specify a character index for the start and end pages.
- (nullable PDFSelection *)selectionFromPage:(PDFPage *)startPage atCharacterIndex:(NSUInteger)startCharacter toPage:(PDFPage *)endPage atCharacterIndex:(NSUInteger)endCharacter;

@end

// Document delegate
@protocol PDFDocumentDelegate< NSObject >
@optional

// Notification delegate methods. If implemented by the delegate, these are called. See notification comments above.
- (void)documentDidUnlock:(NSNotification *)notification;
- (void)documentDidBeginDocumentFind:(NSNotification *)notification;
- (void)documentDidEndDocumentFind:(NSNotification *)notification;
- (void)documentDidBeginPageFind:(NSNotification *)notification;
- (void)documentDidEndPageFind:(NSNotification *)notification;
- (void)documentDidFindMatch:(NSNotification *)notification;

// If implemented by the delegate, called for every search instance found during a find. PDFDocument's implementation 
// accumulates each PDFSelection (instance) in an NSArray.
- (void)didMatchString:(PDFSelection *)instance;

// If implemented by the delegate, will be called when a PDFPage is instantiated. PDFDocument's implementation calls
// -[PDFDocument pageClass] (see above). 
- (Class)classForPage PDFKIT_AVAILABLE(10_6, 11_0);

// If implemented by the delegate, will be called when a PDFAnnotation is instantiated by a page. PDFPage by default
// will instantiate object of class. This allows you to instead return your own PDFAnnotation subclass.
// Return nil for annotation types you do not subclass.
- (Class)classForAnnotationType:(NSString*)annotationType PDFKIT_AVAILABLE(10_13, 11_0);


@end

NS_ASSUME_NONNULL_END
// ==========  PDFKit.framework/Headers/PDFSelection.h
//
//  PDFSelection.h
//  Copyright © 2016 Apple. All rights reserved.
//
//  PDFSelection tracks a range of text on one or many pages, from a starting
//  to end position. From a selection over a range of text, you have the ability
//  to extract the plain-text string or decorated string. PDFSelections can be
//  combined together, combining as needed or keeping the several discrete and
//  non-overlapping selections apart. Selections can also grow and shrink as
//  needed.
//

#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFPage.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFPage, PDFSelectionPrivate;

PDFKIT_CLASS_AVAILABLE(10_4, 11_0)
@interface PDFSelection : NSObject <NSCopying>
{
@private
    PDFSelectionPrivate *_private;
}


// -------- initialization

// Returns and empty PDFSelection. Generally this is not useful but you can use this empty PDFSelection as a container
// into which you -[addSelection] or -[addSelections] below.
- (instancetype)initWithDocument:(PDFDocument *)document PDFKIT_AVAILABLE(10_5, 11_0) NS_DESIGNATED_INITIALIZER;


// -------- accessors

// Array of pages covered by the selection. These are sorted by page index.
@property (nonatomic, readonly) NSArray<PDFPage*> *pages;

// If no color is ever specified, PDFSelections will draw using [NSColor selectedTextBackgroundColor] when active and 
// [NSColor secondarySelectedControlColor] when not active. Calling -[setColor] will force the specified color to be 
// used for both active and inactive drawing.
@property (nonatomic, copy, nullable) PDFKitPlatformColor *color PDFKIT_AVAILABLE(10_5, 11_0);

// String representing the text covered by the selection. May contain line-feeds.
@property (nonatomic, readonly, nullable) NSString *string;
@property (nonatomic, readonly, nullable) NSAttributedString *attributedString;

// Given a PDFPage, returns the bounds in page-space of the text covered by the selection on that page.
// Note that the bounds are relative to the origin of the page content, not the origin of any particular PDFDisplayBox.
- (PDFRect)boundsForPage:(PDFPage *)page;

// Returns the number of contiguous ranges of text on the specified page. Returns zero if page is not in selection.
// A typical, simple selection will contain a single range of text.
- (NSUInteger)numberOfTextRangesOnPage:(PDFPage *)page PDFKIT_AVAILABLE(10_7, 11_0);

// Returns a range of contiguous text at index on the specified page.
// A typical, simple selection will contain a single range of text.
- (NSRange)rangeAtIndex:(NSUInteger)index onPage:(PDFPage *)page PDFKIT_AVAILABLE(10_7, 11_0);

// Returns an array of PDFSelection objects - one for each line of text covered by the receiver. For example if the
// receiver PDFSelection represents a selected paragraph, calling this method would return several PDFSelections - one 
// for each line of text in the paragraph.
- (NSArray<PDFSelection*>*)selectionsByLine PDFKIT_AVAILABLE(10_5, 11_0);

// -------- modifying

// Add a selection to this selection. Selections don't have to be contiguous. If the selection added overlaps with this 
// selection, overlaps are removed.
- (void)addSelection:(PDFSelection *)selection;

// For adding several selections, you can get better performance calling -[addSelections:] and passing in an array of
// PDFSelections than calling -[addSelection] above inside a loop. It is the "normalization" (removing the overlaps) 
// that can be slow when adding a selection to another. This function adds all the selections first and then 
// normalizes just once at the end.
- (void)addSelections:(NSArray<PDFSelection*> *)selections PDFKIT_AVAILABLE(10_5, 11_0);

// Extends the selection at either end. Selections can be extended right off onto neighboring pages even to include the 
// entire PDF document.
- (void)extendSelectionAtEnd:(NSInteger)succeed;
- (void)extendSelectionAtStart:(NSInteger)precede;

// Extend to the selection to the beginning and end of the currently selected lines of text. If the current selection is on a single
// line, then this will extend it to the entire line width. If the selection is across multiple lines, then the first and last
// lines are expected to wholly contain their respective rows of text.
- (void)extendSelectionForLineBoundaries PDFKIT_AVAILABLE(10_13, 11_0);

// -------- rendering

// Calls the below method passing kPDFDisplayBoxCropBox for box.
- (void)drawForPage:(PDFPage *)page active: (BOOL) active;

// Draws the selection in page space relative to the origin of box. Box can be kPDFDisplayBoxMediaBox, 
// kPDFDisplayBoxCropBox, kPDFDisplayBoxBleedBox, kPDFDisplayBoxTrimBox or kPDFDisplayBoxArtBox. If active is true, it 
// is drawn using -[NSColor selectedTextBackgroundColor], otherwise it is drawn using 
// -[NSColor secondarySelectedControlColor].
- (void)drawForPage:(PDFPage *)page withBox:(PDFDisplayBox)box active:(BOOL)active;

@end

NS_ASSUME_NONNULL_END
// ==========  PDFKit.framework/Headers/PDFKit.h
//
//  PDFKit.h
//  Copyright © 2016 Apple. All rights reserved.
//

// Cross-platform support
#import <PDFKit/PDFKitPlatform.h>

// All public headers
#import <PDFKit/PDFAction.h>
#import <PDFKit/PDFActionGoTo.h>
#import <PDFKit/PDFActionNamed.h>
#import <PDFKit/PDFActionResetForm.h>
#import <PDFKit/PDFActionRemoteGoTo.h>
#import <PDFKit/PDFActionURL.h>
#import <PDFKit/PDFAnnotation.h>
#import <PDFKit/PDFAnnotationUtilities.h>
#import <PDFKit/PDFAppearanceCharacteristics.h>
#import <PDFKit/PDFBorder.h>
#import <PDFKit/PDFDestination.h>
#import <PDFKit/PDFDocument.h>
#import <PDFKit/PDFOutline.h>
#import <PDFKit/PDFPage.h>
#import <PDFKit/PDFSelection.h>
#import <PDFKit/PDFThumbnailView.h>
#import <PDFKit/PDFView.h>

// ==========  PDFKit.framework/Headers/PDFKitPlatform.h
//
//  PDFKitPlatform.h
//  PDFKit
//

#import <TargetConditionals.h>

    #define PDFKIT_PLATFORM_IOS


#ifndef PDFKIT_EXTERN
    #ifdef __cplusplus
        #define PDFKIT_EXTERN extern "C" __attribute__((visibility ("default")))
    #else
        #define PDFKIT_EXTERN extern __attribute__((visibility ("default")))
    #endif
#endif

// Deprecation &  macros

#define PDFKIT_AVAILABLE(_macIntro, _iosIntro) \
    NS_AVAILABLE(_macIntro, _iosIntro)

#define PDFKIT_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep) \
    NS_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep)

#define PDFKIT_CLASS_AVAILABLE(_macIntro, _iosIntro) \
    NS_CLASS_AVAILABLE(_macIntro, _iosIntro)

#define PDFKIT_CLASS_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep) \
    NS_CLASS_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep)

#define PDFKIT_ENUM_AVAILABLE(_macIntro, _iosIntro) \
    NS_ENUM_AVAILABLE(_macIntro, _iosIntro)

#define PDFKIT_ENUM_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep) \
    NS_ENUM_DEPRECATED(_macIntro, _macDep, _iosIntro, _iosDep)



// iOS Headers
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

// UIKit types
#define PDFKitPlatformView                                      UIView
#define PDFKitPlatformViewController                            UIViewController
#define PDFKitPlatformScrollView                                UIScrollView
#define PDFKitPlatformColor                                     UIColor
#define PDFKitPlatformBezierPath                                UIBezierPath
#define PDFKitPlatformBezierPathElement                         UIBezierPathElement
#define PDFKitPlatformImage                                     UIImage
#define PDFKitPlatformImageView                                 UIImageView
#define PDFKitPlatformEvent                                     UIEvent
#define PDFKitPlatformFont                                      UIFont
#define PDFKitPlatformColor                                     UIColor
#define PDFKitPlatformControl                                   UIControl
#define PDFKitPlatformTextField                                 UITextField
#define PDFKitPlatformTextFieldDidBeginEditing                  UITextFieldTextDidBeginEditingNotification
#define PDFKitPlatformTextFieldDidChangeText                    UITextFieldTextDidChangeNotification
#define PDFKitPlatformTextFieldDidEndEditing                    UITextFieldTextDidEndEditingNotification
#define PDFKitPlatformTextView                                  UITextView
#define PDFKitPlatformTextViewDidChangeSelection                UITextViewTextDidChangeNotification
#define PDFKitPlatformChoiceWidgetComboBoxView                  UIPickerView
#define PDFKitPlatformChoiceWidgetListView                      UITableView
#define PDFKitPlatformButton                                    UIButton
#define PDFKitPlatformButtonCell                                UICollectionViewCell
#define PDFKitPlatformAccessibilityElement                      UIAccessibilityElement

// Geometry types
#define PDFPoint                                                CGPoint
#define PDFRect                                                 CGRect
#define PDFSize                                                 CGSize
#define PDFEdgeInsets                                           UIEdgeInsets

// Constants
#define PDFPointZero                                            CGPointZero
#define PDFSizeZero                                             CGSizeZero
#define PDFRectZero                                             CGRectZero
#define PDFEdgeInsetsZero                                       UIEdgeInsetsZero


// ==========  PDFKit.framework/Headers/PDFOutline.h
//
//  PDFOutline.h
//  Copyright © 2016 Apple. All rights reserved.
//
//  PDFOutline represents a node in an outline hierarchy, which is always constructed
//  of these node types. A root PDFOutline node can have any number of children,
//  added via the below -[insertChild:atIndex:] method. These children can also have
//  any number of their own child node objects. The relationship between parent and
//  child nodes should never introduce any cycles: the resulting tree should always be
//  a directed acyclic graph.
//

#import <PDFKit/PDFKitPlatform.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFAction, PDFDocument, PDFDestination, PDFOutlinePrivate;

PDFKIT_CLASS_AVAILABLE(10_4, 11_0)
@interface PDFOutline : NSObject // < NSCopying >
{
@private
    PDFOutlinePrivate *_private;
}

// -------- initializer

// Returns a PDFOutline object. If this object is to be the outline root, you will need to add additional PDFOutline
// objects to form the outline hierarchy you desire. You will then need to add it to a PDFDocument by passing it to 
// -[PDFDocument setOutlineRoot:]. If this is to be a child (non-root) outline you will need to set a label for it and 
// either a destination or action for it. Also, you will need to add it as a child of another PDFOutline object.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

// -------- accessors

// The PDFDocument the outline is associated with.
@property (nonatomic, readonly, weak, nullable) PDFDocument *document;

// Returns the parent outline (the root outline will return nil).
@property (nonatomic, readonly, nullable) PDFOutline *parent PDFKIT_AVAILABLE(10_5, 11_0);

// Number of PDFOutline children this PDFOutline has.
@property (nonatomic, readonly) NSUInteger numberOfChildren;

// Returns the index of the outline item - that is, relative to its siblings (and from the perspective of the parent).
// The root outline item (or any item with no parent) is always index 0.
@property (nonatomic, readonly) NSUInteger index PDFKIT_AVAILABLE(10_5, 11_0);

// PDFOutline child at index. Will throw exception if index is out of range.
- (PDFOutline *)childAtIndex:(NSUInteger)index;

// To build up a PDFOutline hierarchy, you call this method to add children outline items. For the simplest of outlines 
// you would, at the very least, have to add items to the outline root item.
// NOTE: Be careful when calling this for a PDFOutline item which already has a parent (for example when moving items 
// around within an outline hierarchy) - you should retain the item and call -[removeFromParent] first.
- (void)insertChild:(PDFOutline *)child atIndex:(NSUInteger)index PDFKIT_AVAILABLE(10_5, 11_0);

// Removes self from parent (for root outline, does nothing since the root has no parent).
- (void)removeFromParent PDFKIT_AVAILABLE(10_5, 11_0);

// The label for the outline. The root PDFOutline has no label and is only a container for children PDFOutlines.
@property (nonatomic, copy, nullable) NSString *label;

// Indicates whether PDFOutline item is initially disclosed or not. If the outline item has no children, -[isOpen] is 
// always NO and calling -[setIsOpen] has no effect. The root item always returns YES for -[isOpen] and calling 
// -[setIsOpen] also has no effect.
@property (nonatomic) BOOL isOpen PDFKIT_AVAILABLE(10_5, 11_0);

// Get: The destination associated with the outline item. The root PDFOutline has no destination. May return nil if the
// outline item has an associated action instead. If however the associated action is a PDFActionGoTo type this method 
// will return the destination from the PDFActionGoTo action. The preferred way though is to call -[action] below.

// Set: Has no effect on the root PDFOutline item. If the item previously had an action associated with it, the action is
// released (PDFOutline items cannot have both an action and a destination, they are mutually exclusive).
// The preferred way though is to call -[setAction] below.
@property (nonatomic, strong, nullable) PDFDestination *destination;

// Action performed when a user clicks on the PDFOutline. Equivalent to calling -[destination] above when the outline 
// has a destination (-[action] will return a PDFActionGoTo object). Some outlines do not have destinations however and 
// you must therefore call this method. The root outline item will never return either an action or a destination.
// Calling -[setAction] on the root item has no effect.

@property (nonatomic, strong, nullable) PDFAction *action PDFKIT_AVAILABLE(10_5, 11_0);

@end

NS_ASSUME_NONNULL_END
