/****************************************************************************
 Copyright (c) 2013      cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "RootViewController.h"
#import "cocos2d.h"
#import "platform/ios/CCEAGLView-ios.h"
#import <Tapjoy/Tapjoy.h>
#include "Adaptor.h"
#import "AppController.h"


@interface RootViewController () <TJPlacementDelegate, TJCVideoAdDelegate>
@property (strong, nonatomic) TJPlacement *directPlayPlacement;
@property (nonatomic, strong) TJDirectPlayPlacementDelegate *dpDelegate;
@end

@implementation RootViewController

/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}

*/

// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskAllButUpsideDown;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
    [super didRotateFromInterfaceOrientation:fromInterfaceOrientation];

    cocos2d::GLView *glview = cocos2d::Director::getInstance()->getOpenGLView();

    if (glview)
    {
        CCEAGLView *eaglview = (CCEAGLView*) glview->getEAGLView();

        if (eaglview)
        {
            CGSize s = CGSizeMake([eaglview getWidth], [eaglview getHeight]);
            cocos2d::Application::getInstance()->applicationScreenSizeChanged((int) s.width, (int) s.height);
        }
    }
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];

    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
    _directPlayPlacement.delegate = nil;

}

//------------------------------------------------------------------------------------------------------------//
//------- GameKit Delegate -----------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//
#pragma mark - GameKit Delegate

- (void)gameCenterViewControllerDidFinish:(GKGameCenterViewController *)gameCenterViewController {
    [self dismissViewControllerAnimated:YES completion:nil];
    if (gameCenterViewController.viewState == GKGameCenterViewControllerStateAchievements) {
    } else if (gameCenterViewController.viewState == GKGameCenterViewControllerStateLeaderboards) {
    } else {
    }
}

//------------------------------------------------------------------------------------------------------------//
//------- GameCenter Manager Delegate ------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//
#pragma mark - GameCenter Manager Delegate

- (void)gameCenterManager:(GameCenterManager *)manager authenticateUser:(UIViewController *)gameCenterLoginController {
    [self presentViewController:gameCenterLoginController animated:YES completion:^{
        NSLog(@"Finished Presenting Authentication Controller");
    }];
}

- (void)gameCenterManager:(GameCenterManager *)manager availabilityChanged:(NSDictionary *)availabilityInformation {
    NSLog(@"GC Availabilty: %@", availabilityInformation);
    if ([[availabilityInformation objectForKey:@"status"] isEqualToString:@"GameCenter Available"]) {
        [self.navigationController.navigationBar setValue:@"GameCenter Available" forKeyPath:@"prompt"];
    } else {
        [self.navigationController.navigationBar setValue:@"GameCenter Unavailable" forKeyPath:@"prompt"];
    }
    
    GKLocalPlayer *player = [[GameCenterManager sharedManager] localPlayerData];
    if (player) {
        if ([player isUnderage] == NO) {
                  [[GameCenterManager sharedManager] localPlayerPhoto:^(UIImage *playerPhoto) {
            }];
        } else {
                 }
    } else {
    }
}

- (void)gameCenterManager:(GameCenterManager *)manager error:(NSError *)error {
    
}

- (void)gameCenterManager:(GameCenterManager *)manager reportedAchievement:(GKAchievement *)achievement withError:(NSError *)error {
    if (!error) {
    } else {
    }
}

- (void)gameCenterManager:(GameCenterManager *)manager reportedScore:(GKScore *)score withError:(NSError *)error {
    if (!error) {
    } else {
    }
}

- (void)gameCenterManager:(GameCenterManager *)manager didSaveScore:(GKScore *)score {
}

- (void)gameCenterManager:(GameCenterManager *)manager didSaveAchievement:(GKAchievement *)achievement {
}


#pragma mark - Tapjoy Related Methods
- (void) requestTapJoyVideo
{
    [Tapjoy setVideoAdDelegate:self];
    
    _dpDelegate = [[TJDirectPlayPlacementDelegate alloc] init];
    _dpDelegate.rtViewController = self;
    
    _directPlayPlacement = [TJPlacement placementWithName:@"video" delegate:_dpDelegate];
    [_directPlayPlacement requestContent];

}

- (void)getDirectPlayVideoAdAction
{    
    if(_directPlayPlacement.isContentAvailable)
    {
        if(_directPlayPlacement.isContentReady)
        {
            [_directPlayPlacement showContentWithViewController:self.tabBarController];
        }
        else
        {
            Adaptor::videoFail();
        }
    }
    else
    {
        Adaptor::videoNotContent();
    }
}


#pragma mark Tapjoy Video

- (void)videoAdCompleted {
    NSLog(@"videoAdCompleted");
    Adaptor::videoSuccess();
}


#pragma mark TJPlacementDelegate methods

- (void)requestDidSucceed:(TJPlacement*)placement
{
    NSLog(@"Tapjoy request content complete, isContentAvailable:%d", placement.isContentAvailable);

    // Make sure we recieved content from the event call
    if(placement.isContentAvailable) {
    }
}

- (void)contentIsReady:(TJPlacement*)placement
{
    NSLog(@"Tapjoy placement content is ready to display");
}

- (void)requestDidFail:(TJPlacement*)placement error:(NSError *)error
{
    //AdaptoriOS::videoFail();
    NSLog(@"Tapjoy request content failed with error: %@", [error localizedDescription]);

}

- (void)contentDidAppear:(TJPlacement*)placement
{
    NSLog(@"Content did appear for %@ placement", [placement placementName]);
}

- (void)contentDidDisappear:(TJPlacement*)placement
{
    NSLog(@"Content did disappear for %@ placement", [placement placementName]);
}

- (void)placement:(TJPlacement*)placement didRequestPurchase:(TJActionRequest*)request productId:(NSString*)productId
{
    // Your app must call either completed or cancelled to complete the lifecycle of the request
    [request completed];
}


- (void)placement:(TJPlacement*)placement didRequestReward:(TJActionRequest*)request itemId:(NSString*)itemId quantity:(int)quantity
{
    // Your app must call either completed or cancelled to complete the lifecycle of the request
    [request completed];
}


- (void)placement:(TJPlacement*)placement didRequestCurrency:(TJActionRequest*)request currency:(NSString*)currency amount:(int)amount
{
     // Your app must call either completed or cancelled to complete the lifecycle of the request
    [request completed];
}


- (void)placement:(TJPlacement*)placement didRequestNavigation:(TJActionRequest*)request location:(NSString *)location
{
     // Your app must call either completed or cancelled to complete the lifecycle of the request
    [request completed];
}
@end

#pragma mark TJPlacementDelegate

@interface TJDirectPlayPlacementDelegate ()

@end

@implementation TJDirectPlayPlacementDelegate
-(id)init
{
    self = [super init];
    
    if (self)
    {}
    
    return self;
}

- (void)requestDidSucceed:(TJPlacement*)placement
{
    NSLog(@"Tapjoy request did succeed, contentIsAvailable:%d", placement.isContentAvailable);
}

- (void)contentIsReady:(TJPlacement*)placement
{
    NSLog(@"Tapjoy placement content is ready to display");
}

- (void)requestDidFail:(TJPlacement*)placement error:(NSError *)error
{
    Adaptor::videoFail();
    NSLog(@"Tapjoy request failed with error: %@", [error localizedDescription]);
}

- (void)contentDidAppear:(TJPlacement*)placement
{
    NSLog(@"Content did appear for %@ placement", [placement placementName]);
}

- (void)contentDidDisappear:(TJPlacement*)placement
{
    AppController *app = (AppController *)[[UIApplication sharedApplication] delegate];
    [app.viewController requestTapJoyVideo];
    Adaptor::videoFail();
}
@end

