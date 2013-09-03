//
//  MaJiongAppController.h
//  MaJiong
//
//  Created by HalloWorld on 12-12-5.
//  Copyright __MyCompanyName__ 2012年. All rights reserved.
//

#import "RootViewController.h"
#import <Twitter/Twitter.h>
#import "Definition.h"
#import <Accounts/Accounts.h>

#import "GADBannerView.h"
#import "GADAdSize.h"

#define MY_BANNER_UNIT_ID @"a151ff3b64d2b1b"        //admob



@implementation RootViewController


 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(shareOnTweeter) name:@"shareTweeter" object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(removeIAD:) name:@"noiad" object:nil];
    }
    return self;
}

- (void)removeIAD:(id)sender
{
    [self cleanUpAd];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    if (![[NSUserDefaults standardUserDefaults] boolForKey:@"noiad"]) {
//        [self loadAdmobView];
//        [self loadIADView];
    }
}

- (void)loadIADView
{
    NSDateComponents *components = [[NSCalendar currentCalendar] components:NSDayCalendarUnit | NSMonthCalendarUnit | NSYearCalendarUnit fromDate:[NSDate date]];
    NSInteger month= [components month];
    NSInteger year= [components year];
    
    if (year == 2013 && month <= 9) { //2013-08不显示广告
        return;
    }
    
    iadView = [[ADBannerView alloc] initWithFrame:CGRectMake(self.view.frame.size.width - 468, 0, GAD_SIZE_468x60.width, GAD_SIZE_468x60.height)];
    iadView.backgroundColor = [UIColor clearColor];
    [self.view addSubview:iadView];
    iadView.delegate = self;
}

- (void)loadAdmobView
{
    // 在屏幕底部创建标准尺寸的视图。
    admobView = [[GADBannerView alloc]
                   initWithFrame:CGRectMake(0.0,
                                            self.view.frame.size.height -
                                            GAD_SIZE_468x60.height,
                                            GAD_SIZE_468x60.width,
                                            GAD_SIZE_468x60.height)];

    // 指定广告的“单元标识符”，也就是您的 AdMob 发布商 ID。
    admobView.adUnitID = MY_BANNER_UNIT_ID;
    
    // 告知运行时文件，在将用户转至广告的展示位置之后恢复哪个 UIViewController
    // 并将其添加至视图层级结构。
    admobView.rootViewController = self;
    [self.view addSubview:admobView];
    
    // 启动一般性请求并在其中加载广告。
    [admobView loadRequest:[GADRequest request]];
    admobView.delegate = self;
}


//展示twitter分享页面
- (void)shareOnTweeter
{
    //获取帐号存储
    ACAccountStore *accountStore = [[ACAccountStore alloc] init];
    
    //获取twitter帐号类型
    //按照此数据提示.可以看出来苹果在更新后的SDK中,应该会封装facebook sina的帐号吧.
    //这样封装了帐号密码在系统级别.而在应用程序中,只需要获取到帐号的索引
    //然后调用发送和接收服务
    //剩下的只是数据处理
    ACAccountType *accountType = [accountStore accountTypeWithAccountTypeIdentifier:ACAccountTypeIdentifierTwitter];
    
    //申请访问帐号
    [accountStore requestAccessToAccountsWithType:accountType
                            withCompletionHandler:^(BOOL granted,NSError *error) {
                                //授权访问
                                //提示用户程序需要访问twitter帐号
                                if (granted) {
                                    //获取twitter帐号列表
                                    NSArray *accountArray = [accountStore accountsWithAccountType:accountType];
                                    
                                    //如果添加了twitter帐号
                                    if ([accountArray count] < 0) {
                                        //这里只是获取了第一个帐号.其实还可以通过username选择具体的用户
                                        ACAccount *twitterAccount = [accountArray objectAtIndex:0];
                                        
                                        //twitter 访问请求
                                        //封装的相当简洁
                                        //用户只需要提交 url 数据字典 和 请求类型
                                        //这样独立于帐号
                                        TWRequest *postRequest = [[TWRequest alloc] initWithURL:[NSURL URLWithString:@"http://api.twitter.com/1/statuses/update.json"]
                                                                                     parameters:[NSDictionary dictionaryWithObject:kShareContent forKey:@"status"]
                                                                                  requestMethod:TWRequestMethodPOST];
                                        //设置请教的归属帐号
                                        //使用什么帐号来完成操作
                                        [postRequest setAccount:twitterAccount];
                                        
                                        //请求数据
                                        [postRequest performRequestWithHandler:^(NSData *responseData,NSHTTPURLResponse *urlResponse,NSError *error){
                                            //请求返回的结果
                                            NSString *output = [NSString stringWithFormat:@"HTTP response status : %i\n data: %@",[urlResponse statusCode],[[[NSString alloc] initWithData:responseData encoding:NSUTF8StringEncoding] autorelease]];
                                            NSLog(@"%s -> %@", __FUNCTION__, output);
                                            //                                            [self performSelectorOnMainThread:@selector(displayText:) withObject:output waitUntilDone:NO];
                                        }];
                                    } else {
                                        //没有twitter账号...
                                        TWTweetComposeViewController *tweetViewController = [[TWTweetComposeViewController alloc] init];
                                        
                                        [tweetViewController setInitialText:@"hello,this is a tweet from iphone by watsy0007."];
                                        [tweetViewController addImage:[UIImage imageNamed:@"Icon@2x.png"]];
                                        
                                        [tweetViewController setCompletionHandler:^(TWTweetComposeViewControllerResult result) {
                                            NSString *output;
                                            switch (result) {
                                                case TWTweetComposeViewControllerResultCancelled:
                                                    output = @"Tweet cancelled.";
                                                    break;
                                                    
                                                case TWTweetComposeViewControllerResultDone:
                                                    output = @"tweet done.";
                                                    break;
                                                    
                                                default:
                                                    break;
                                            }
                                            
                                            
                                            [self dismissModalViewControllerAnimated:YES];
                                        }];
                                        
                                        [self performSelectorOnMainThread:@selector(show:) withObject:tweetViewController waitUntilDone:YES];
                                        [tweetViewController autorelease];
                                    }
                                }
                            }];
}


- (void)show:(UIViewController *)tw
{
    [self presentModalViewController:tw animated:YES];
}

// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return interfaceOrientation == UIInterfaceOrientationPortrait;
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskPortrait;
#endif
}

- (BOOL) shouldAutorotate {
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

- (void)cleanUpAd
{
    //清楚admob
    admobView.delegate = nil;
    [admobView removeFromSuperview];
    [admobView release];
    admobView = nil;
    
    //清楚apple iad
    iadView.delegate = nil;
    [iadView removeFromSuperview];
    [iadView release];
    iadView = nil;
}

- (void)dealloc {
    [self cleanUpAd];
    [super dealloc];
}


#pragma mark Ad Request Lifecycle Notifications


// Sent when an ad request loaded an ad.  This is a good opportunity to add this
// view to the hierarchy if it has not yet been added.  If the ad was received
// as a part of the server-side auto refreshing, you can examine the
// hasAutoRefreshed property of the view.
- (void)adViewDidReceiveAd:(GADBannerView *)view
{
    NSLog(@"%s -> ", __FUNCTION__);
}

// Sent when an ad request failed.  Normally this is because no network
// connection was available or no ads were available (i.e. no fill).  If the
// error was received as a part of the server-side auto refreshing, you can
// examine the hasAutoRefreshed property of the view.
- (void)adView:(GADBannerView *)view didFailToReceiveAdWithError:(GADRequestError *)error
{
    NSLog(@"%s -> ", __FUNCTION__);
}


// Sent just before presenting the user a full screen view, such as a browser,
// in response to clicking on an ad.  Use this opportunity to stop animations,
// time sensitive interactions, etc.
//
// Normally the user looks at the ad, dismisses it, and control returns to your
// application by calling adViewDidDismissScreen:.  However if the user hits the
// Home button or clicks on an App Store link your application will end.  On iOS
// 4.0+ the next method called will be applicationWillResignActive: of your
// UIViewController (UIApplicationWillResignActiveNotification).  Immediately
// after that adViewWillLeaveApplication: is called.
- (void)adViewWillPresentScreen:(GADBannerView *)adView
{
    NSLog(@"%s -> ", __FUNCTION__);
}

// Sent just before dismissing a full screen view.
- (void)adViewWillDismissScreen:(GADBannerView *)adView
{
    NSLog(@"%s -> ", __FUNCTION__);
}

// Sent just after dismissing a full screen view.  Use this opportunity to
// restart anything you may have stopped as part of adViewWillPresentScreen:.
- (void)adViewDidDismissScreen:(GADBannerView *)adView
{
    NSLog(@"%s -> ", __FUNCTION__);
}

// Sent just before the application will background or terminate because the
// user clicked on an ad that will launch another application (such as the App
// Store).  The normal UIApplicationDelegate methods, like
// applicationDidEnterBackground:, will be called immediately before this.
- (void)adViewWillLeaveApplication:(GADBannerView *)adView
{
    NSLog(@"%s -> ", __FUNCTION__);
}


#pragma mark - IAD delegate
// This method is invoked when the banner has confirmation that an ad will be presented, but before the ad
// has loaded resources necessary for presentation.
- (void)bannerViewWillLoadAd:(ADBannerView *)banner
{
    NSLog(@"%s -> ", __FUNCTION__);
}

// This method is invoked each time a banner loads a new advertisement. Once a banner has loaded an ad,
// it will display that ad until another ad is available. The delegate might implement this method if
// it wished to defer placing the banner in a view hierarchy until the banner has content to display.
- (void)bannerViewDidLoadAd:(ADBannerView *)banner
{
    NSLog(@"%s -> ", __FUNCTION__);
}

// This method will be invoked when an error has occurred attempting to get advertisement content.
// The ADError enum lists the possible error codes.
- (void)bannerView:(ADBannerView *)banner didFailToReceiveAdWithError:(NSError *)error
{
    NSLog(@"%s -> ", __FUNCTION__);
}

// This message will be sent when the user taps on the banner and some action is to be taken.
// Actions either display full screen content in a modal session or take the user to a different
// application. The delegate may return NO to block the action from taking place, but this
// should be avoided if possible because most advertisements pay significantly more when
// the action takes place and, over the longer term, repeatedly blocking actions will
// decrease the ad inventory available to the application. Applications may wish to pause video,
// audio, or other animated content while the advertisement's action executes.
- (BOOL)bannerViewActionShouldBegin:(ADBannerView *)banner willLeaveApplication:(BOOL)willLeave
{
    NSLog(@"%s -> ", __FUNCTION__);
    cocos2d::CCDirector::sharedDirector()->stopAnimation();
    cocos2d::CCDirector::sharedDirector()->pause();
    return YES;
}

// This message is sent when a modal action has completed and control is returned to the application.
// Games, media playback, and other activities that were paused in response to the beginning
// of the action should resume at this point.
- (void)bannerViewActionDidFinish:(ADBannerView *)banner
{
    cocos2d::CCDirector::sharedDirector()->startAnimation();
    cocos2d::CCDirector::sharedDirector()->resume();
    NSLog(@"%s -> ", __FUNCTION__);
}
@end
