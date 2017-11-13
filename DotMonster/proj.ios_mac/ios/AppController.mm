/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org

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

#import "AppController.h"
#import "platform/ios/CCEAGLView-ios.h"
#import "cocos2d.h"
#import "AppDelegate.h"
#import "RootViewController.h"
#import <Tapjoy/Tapjoy.h>
#import "GameCenterManager.h"

@implementation AppController

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    

    cocos2d::Application *app = cocos2d::Application::getInstance();
    app->initGLContextAttrs();
    cocos2d::GLViewImpl::convertAttrs();
    
    // Override point for customization after application launch.
    
    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    
    // Init the CCEAGLView
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [window bounds]
                                         pixelFormat: (NSString*)cocos2d::GLViewImpl::_pixelFormat
                                         depthFormat: cocos2d::GLViewImpl::_depthFormat
                                  preserveBackbuffer: NO
                                          sharegroup: nil
                                       multiSampling: NO
                                     numberOfSamples: 0 ];
    
    // Use RootViewController manage CCEAGLView
    _viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    _viewController.wantsFullScreenLayout = YES;
    _viewController.view = eaglView;
    
    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: _viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:_viewController];
    }
    
    [window makeKeyAndVisible];
    
    [[UIApplication sharedApplication] setStatusBarHidden:true];
    
    // IMPORTANT: Setting the GLView should be done after creating the RootViewController
    cocos2d::GLView *glview = cocos2d::GLViewImpl::createWithEAGLView(eaglView);
    cocos2d::Director::getInstance()->setOpenGLView(glview);
    
    app->run();
    
    _bannerView = [[GADBannerView alloc] initWithAdSize:kGADAdSizeBanner];
    _bannerView.adUnitID = @"ca-app-pub-4632355628993989/8124695555";
    _bannerView.rootViewController = _viewController;
    _bannerView.frame = CGRectMake(_viewController.view.center.x-160, 0, 320, 50);
    [_viewController.view addSubview:_bannerView];
    [_bannerView loadRequest:[GADRequest request]];
    
    [self createInterstital];
    
    // Tapjoy Connect Notifications
    /*
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(tjcConnectSuccess:)
                                                 name:TJC_CONNECT_SUCCESS
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(tjcConnectFail:)
                                                 name:TJC_CONNECT_FAILED
                                               object:nil];
    */
    // Registering for remote notifications
    /*
    if ([application respondsToSelector:@selector(isRegisteredForRemoteNotifications)])
    {
        // iOS 8 Notifications
        [application registerUserNotificationSettings:[UIUserNotificationSettings settingsForTypes:(UIUserNotificationTypeSound | UIUserNotificationTypeAlert | UIUserNotificationTypeBadge) categories:nil]];
        [application registerForRemoteNotifications];
    }
    else
    {
        // iOS < 8 Notifications
        [application registerForRemoteNotificationTypes:
         (UIRemoteNotificationTypeBadge | UIRemoteNotificationTypeAlert | UIRemoteNotificationTypeSound)];
    }
    */
    [Tapjoy connect:@"Uqmuuk8SS92s5i9OhhNpPQEB1viVYq5Gmq5bYbBxt6wLDIRaXp1O0MKX85PL"];
    [Tapjoy setDebugEnabled:NO];
    
    [[GameCenterManager sharedManager] setupManager];
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->pause(); */
    [[NSNotificationCenter defaultCenter] removeObserver:self name:TJC_CURRENCY_EARNED_NOTIFICATION object:nil];
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->resume(); */
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(showEarnedCurrencyAlert:)
                                                 name:TJC_CURRENCY_EARNED_NOTIFICATION
                                               object:nil];
    [Tapjoy getCurrencyBalance];

}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::Application::getInstance()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::Application::getInstance()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}


- (void)dealloc {
    [window release];
    [super dealloc];
}

#pragma mark -


- (void)showAdMob
{
    [_bannerView setHidden:NO];
}

- (void)hideAdMob
{
    [_bannerView setHidden:YES];
    
}

- (void)showInterstital
{
    if ([_interstitalView isReady]) {
        [_interstitalView presentFromRootViewController:_viewController];
    }

}
- (void)createInterstital
{
    _interstitalView = [[GADInterstitial alloc] initWithAdUnitID:@"ca-app-pub-4632355628993989/9601428756"];
    _interstitalView.delegate = self;
    [_interstitalView loadRequest:[GADRequest request]];
}
- (void)loginGameCenter
{
    // Set GameCenter Manager Delegate
   [[GameCenterManager sharedManager] setDelegate:_viewController];
    
}
- (void)sendSocre:(int)score
{
    [[GameCenterManager sharedManager] saveAndReportScore:score leaderboard:@"SealMonster" sortOrder:GameCenterSortOrderHighToLow];
}
- (void)showLeaderBoard
{
    [[GameCenterManager sharedManager] presentAchievementsOnViewController:_viewController];
}
#pragma mark -
- (void)interstitialDidDismissScreen:(GADInterstitial *)interstitial {
    [self createInterstital];
}

#pragma mark -
- (void)showVideo
{
    [_viewController getDirectPlayVideoAdAction];
}
-(void)tjcConnectSuccess:(NSNotification*)notifyObj
{
    NSLog(@"Tapjoy connect Succeeded");
    [_viewController requestTapJoyVideo];
}
-(void)tjcConnectFail:(NSNotification*)notifyObj
{
    NSLog(@"Tapjoy connect Failed");
}
- (void)showEarnedCurrencyAlert:(NSNotification*)notifyObj
{
    NSNumber *currencyEarned = notifyObj.object;
    int earnedNum = [currencyEarned intValue];
    
    NSLog(@"Currency earned: %d", earnedNum);
    
    // Pops up a UIAlert notifying the user that they have successfully earned some currency.
    // This is the default alert, so you may place a custom alert here if you choose to do so.
    [Tapjoy showDefaultEarnedCurrencyAlert];
}

- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
    NSLog(@"didRegisterForRemoteNotificationsWithDeviceToken: %@", deviceToken);
    [Tapjoy setDeviceToken: deviceToken];
}

- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error {
    NSLog(@"didFailToRegisterForRemoteNotificationsWithError: %@", error);
}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo {
    [Tapjoy setReceiveRemoteNotification:userInfo];
}
@end
