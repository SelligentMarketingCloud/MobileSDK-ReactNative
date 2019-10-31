//
//  SMStylingProperties.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 29/04/16.
//  Copyright © 2016 Selligent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SMContentAlignment.h"



/*!
 *  #SMInAppContentStyleOptions :#
 */
@interface SMInAppContentStyleOptions : NSObject


/*!
 *  inform the sdk if the main container view  of your in app content must be scrollable
 *  @discussion bool
 *  By default, it is set to true
 */
@property (nonatomic) bool  mainViewIsScrollable;

/*!
 *  Set the main container view of your in app contents background color
 *  @discussion UIColor
 *  By default, it is clearColor
 */
@property (nonatomic) UIColor  *mainViewBackgroundColor;


/*!
 *  Set the UIActivityIndicator style
 *  @discussion UIActivityIndicatorViewStyle
 *  By default, it is UIActivityIndicatorViewStyleGray
 */
@property (nonatomic) UIActivityIndicatorViewStyle activityIndicatorStyle;


/*!
 *  Set the boolean to determine if status bar must be hidden or not
 *  @discussion bool
 *  By default, it is NO
 */
@property (nonatomic) bool  isStatusBarHidden;


/*!
 *  #Syling options for Box :#
 */

/*!
*  Set the leading constant between edge of view and every in app content box
*  @discussion CGFloat must be a positive value
*  By default, it is set to 10
*/
@property (nonatomic) CGFloat boxLeading;

/*!
 *  Set the trailing constant between edge of view and every in app content box
 *  @discussion CGFloat must be a positive value
 *  By default, it is set to 10
 */
@property (nonatomic) CGFloat boxTrailing;

/*!
 *  Set the Margin between bottom of a box and top of next one 
 *  @discussion CGFloat must be a positive value
 *  By default, it is set to 20
 */
@property (nonatomic) CGFloat marginBetweenBoxes;

/*!
 *  Set the Margin between top of first box and top of view
 *  @discussion CGFloat must be a positive value
 *  By default, it is set to 20
 */
@property (nonatomic) CGFloat marginBetweenFirstBoxAndTopOfView;

/*!
 *  Set the Margin between bottom of last box and bottom of view
 *  @discussion CGFloat must be a positive value
 *  By default, it is set to 20
 */
@property (nonatomic) CGFloat marginBetweenLastBoxAndBottomOfView;

/*!
 *  Set the border width for all boxes
 *  @discussion CGFloat must be a positive value
 *  By default, it is set to 1
 */
@property (nonatomic) CGFloat boxBorderWidth;

/*!
 *  Set the color of box Border
 *  @discussion UIColor
 *  By default, it is set to [UIColor colorWithRed:0.5 green:0.5 blue:0.5 alpha:0.8]
 */
@property (nonatomic) UIColor *boxBorderColor;

/*!
 *  Set the radius of the corner for all boxes
 *  @discussion CGFloat must be a positive value
 *  By default, it is set not set
 */
@property (nonatomic) CGFloat boxCornerRadius;

/*!
 *  Set the background color of all boxes
 *  @discussion UIColor
 *  By default, it is clearColor
 */
@property (nonatomic) UIColor *boxBackgroundColor;


/*!
 *  Set the shadow color of all boxes
 *  @discussion UIColor
 *  By default, it is not set
 */
@property (nonatomic) UIColor *boxShadowColor;


/*!
 *  Set the shadow opacity of all boxes
 *  @discussion CGFloat
 *  By default, it is not set
 */
@property (nonatomic) CGFloat boxShadowOpacity;

/*!
 *  Set the shadow radius of all boxes
 *  @discussion CGFloat
 *  By default, it is not set
 */
@property (nonatomic) CGFloat boxShadowRadius;

/*!
 *  Set the shadow offset of all boxes
 *  @discussion CGSize
 *  By default, it is not set
 */
@property (nonatomic) CGSize boxShadowOffset;


/*!
 *  #Syling options for Title :#
 */

/*!
 *  Set the border width for title
 *  @discussion CGFloat
 *  By default, it is not set
 */
@property (nonatomic) CGFloat titleBorderWidth;


/*!
 *  Set the color of title border
 *  @discussion UIColor
 *  By default, it is not set
 */
@property (nonatomic) UIColor *titleBorderColor;

/*!
 *  Set the radius of the corner for all boxes
 *  @discussion CGFloat
 *  By default, it is not set
 */
@property (nonatomic) CGFloat titleCornerRadius;

/*!
 *  Set the background color of all titles
 *  @discussion UIColor
 *  By default, it is whiteColor
 */
@property (nonatomic) UIColor *titleBackgroundColor;

/*!
 *  Set the number of lines of all titles
 *  @discussion UIColor
 *  By default, it is 0
 */
@property (nonatomic) CGFloat titleNumberOfLines;


/*!
 *  Set the NSLineBreakMode of all titles
 *  @discussion NSLineBreakMode
 *  By default, it is NSLineBreakByWordWrapping 
 */
@property (nonatomic) NSLineBreakMode titleLineBreakMode;


/*!
 *  Set the title text alignment
 *  @discussion NSTextAlignment
 *  By default, it is NSTextAlignmentLeft
 */
@property (nonatomic) NSTextAlignment titleTextAlignment;


/*!
 *  Set the attributes that will be passed to NSAttributedString init which will create the text that will be display for title
 *  @discussion NSDictionary
 *  By default, it is nil
 */
@property (nonatomic) NSDictionary *titleAttributes;


/*!
 *  Set title text color
 *  @discussion UIColor
 *  By default, it is iOS default
 */
@property (nonatomic) UIColor *titleTextColor;


/*!
 *  Set font of the title
 *  @discussion UIFont
 *  By default, it is iOS default
 */
@property (nonatomic) UIFont *titleFont;

/*!
 *  Set the trailing between the title container and the box
 *  @discussion CGFloat
 *  By default, it is 10.0
 */
@property (nonatomic) CGFloat titleTrailing;

/*!
 *  Set the leading between the title container and the box
 *  @discussion CGFloat
 *  By default, it is 10.0
 */
@property (nonatomic) CGFloat titleLeading;

/*!
 *  Set the top between the title container and the box
 *  @discussion CGFloat
 *  By default, it is 30.0
 */
@property (nonatomic) CGFloat titleTop;

/*!
 *  Set the shadow color of all titles
 *  @discussion UIColor
 *  By default, it is not set
 */
@property (nonatomic) UIColor *titleShadowColor;

/*!
 *  Set the shadow opacity of all titles
 *  @discussion CGFloat
 *  By default, it is not set
 */
@property (nonatomic) CGFloat titleShadowOpacity;

/*!
 *  Set the corner radius of all titles
 *  @discussion CGFloat
 *  By default, it is not set
 */
@property (nonatomic) CGFloat titleShadowRadius;

/*!
 *  Set the shadow offset  of all titles
 *  @discussion CGSize
 *  By default, it is not set
 */
@property (nonatomic) CGSize titleShadowOffset;

/*!
 *  Set the bool that will tell if a border bottom must be displayed under all titles in box
 *  @discussion bool
 *  By default, it is NO
 */
@property (nonatomic) bool showTitleBorderBottom;

/*!
 *  Set the border color of all border bottom that are displayed under all titles in box
 *  @discussion UIColor
 *  By default, it is not set
 */
@property (nonatomic) UIColor *titleBorderBottomColor;




/*!
 *  #Syling options for TextView :#
 */


/*!
 *  Set the trailing between the textview and the box
 *  @discussion CGFloat
 *  By default, it is 10.0
 */
@property (nonatomic) CGFloat textViewTrailing;

/*!
 *  Set the leading between the textview and the box
 *  @discussion CGFloat
 *  By default, it is 10.0
 */
@property (nonatomic) CGFloat textViewLeading;

/*!
 *  Set the top between the textview and the box
 *  @discussion CGFloat
 *  By default, it is 10.0
 */
@property (nonatomic) CGFloat textViewTop;

/*!
 *  Set the textview content offset 
 *  @discussion CGPoint
 *  By default, it is not set
 */
@property (nonatomic) CGPoint textViewContentOffset;

/*!
 *  Set the textview content edge inset
 *  @discussion UIEdgeInsets
 *  By default, it is not set
 */
@property (nonatomic) UIEdgeInsets textViewContentInset;

/*!
 *  Set the border width for textview
 *  @discussion CGFloat
 *  By default, it is not set
 */
@property (nonatomic) CGFloat textViewBorderWidth;

/*!
 *  Set the color of textview Border
 *  @discussion UIColor
 *  By default, it is not set
 */
@property (nonatomic) UIColor *textViewBorderColor;

/*!
 *  Set the radius of the corner for all textview
 *  @discussion CGFloat
 *  By default, it is not set
 */
@property (nonatomic) CGFloat textViewCornerRadius;


/*!
 *  Set the background color of textview
 *  @discussion UIColor
 *  By default, it is whiteColor
 */
@property (nonatomic) UIColor *textViewBackgroundColor;

/*!
 *   textview text color and font can be modified both in html set in content of the In App Content payload received by the SDK or another possibility is to apply them with UIAppearance class for specific class
 *   for example :
 *    [[UITextView appearanceWhenContainedIn:[SMInAppContentHTMLViewController class], nil] setFont:[UIFont fontWithName:@"Marker Felt" size:10]];
 *    [[UITextView appearanceWhenContainedIn:[SMInAppContentHTMLViewController class], nil] setTextColor:[UIColor redColor]];
 */


/*!
 *  #Syling options for Links :#
 */


/*!
 *  Set position of the links, this can be Left, Right, or Center
 *  @discussion SMContentAlignment
 *  By default, it is kSMAlignLeft
 */
@property (nonatomic) SMContentAlignment linksAlignment;

/*!
 *  Set the constant margin between links and edge of box (depends also of the linksAlignment property: if linksAligment is kSMAlignLeft than this property will only be applied for Leading margin, if linksAlignment is kSMAlignRight than this property is applied to trailing margin, if linksAlignment is kSMAlignCenter than this property is applied both for leading and trailing)
 *  @discussion CGFloat
 *  By default, it is 10
 */
@property (nonatomic) CGFloat linksMargin;

/*!
 *  Set the constant between links top and bottom of textview
 * @discussion CGFloat
 * By default  it is 10
 */
@property (nonatomic) CGFloat linksTop;

/*!
 *  Set the constant between links bottom and bottom of box
 * @discussion CGFloat
 * By default  it is 10
 */
@property (nonatomic) CGFloat linksBottom;

/*!
 *  Set the constant between links margin - useful when there is two links that will be displayed
 * @discussion CGFloat
 * By default  it is 10
 */
@property (nonatomic) CGFloat marginBetweenLinks;

/*!
 *  Set the border width for links
 *  @discussion CGFloat
 *  By default, it is not set
 */
@property (nonatomic) CGFloat linkBorderWidth;

/*!
 *  Set the color of link  Border
 *  @discussion UIColor
 *  By default, it is not set
 */
@property (nonatomic) UIColor *linkBorderColor;

/*!
 *  Set the corner radius for links
 *  @discussion CGFloat
 *  By default, it is not set
 */
@property (nonatomic) CGFloat linkCornerRadius;


/*!
 *  Set the shadow color of all links
 *  @discussion UIColor
 *  By default, it is not set
 */
@property (nonatomic) UIColor *linkShadowColor;


/*!
 *  Set the shadow opacity of all links
 *  @discussion CGFloat
 *  By default, it is not set
 */
@property (nonatomic) CGFloat linkShadowOpacity;

/*!
 *  Set the shadow radius of all links
 *  @discussion CGFloat
 *  By default, it is not set
 */
@property (nonatomic) CGFloat linkShadowRadius;

/*!
 *  Set the shadow offset of all links
 *  @discussion CGSize
 *  By default, it is not set
 */
@property (nonatomic) CGSize linkShadowOffset;

/*!
 *  Set the background color of link
 *  @discussion UIColor
 *  By default, it is whiteColor
 */
@property (nonatomic) UIColor *linkBackgroundColor;

/*!
 *  Set the text color in link
 *  @discussion UIColor
 *  By default, it is whiteColor
 */@property (nonatomic) UIColor *linkTextColor;

/*!
 *  Set the font of links
 *  @discussion UIFont
 *  By default, it is iOS default
 */
@property (nonatomic) UIFont *linkFont;

/*!
 *  Set the link content edge inset
 *  @discussion UIEdgeInsets
 *  By default, it is not set
 */
@property (nonatomic) UIEdgeInsets linkContentEdgeInsets;




/*!
 * @abstract SMInAppContentStyleOptions constructor
 * @return SMInAppContentStyleOptions
 */
+ (instancetype) defaultStylingOptions;

@end
