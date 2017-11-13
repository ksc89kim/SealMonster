#import <UIKit/UIKit.h>
#import <GoogleMobileAds/GoogleMobileAds.h>

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate,GADInterstitialDelegate> {
    UIWindow *window;

}

@property(nonatomic, readonly) RootViewController* viewController;
@property(nonatomic, readonly) GADBannerView* bannerView;
@property(nonatomic, readonly) GADInterstitial* interstitalView;

- (void)showAdMob;
- (void)hideAdMob;
- (void)showInterstital;
- (void)createInterstital;
- (void)showVideo;
- (void)loginGameCenter;
- (void)sendSocre:(int)score;
- (void)showLeaderBoard;

@end
