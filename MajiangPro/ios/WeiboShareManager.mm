//
//  WeiboShareManager.m
//  MaJiong
//
//  Created by Kira on 8/1/13.
//
//

#import "WeiboShareManager.h"
#import "SinaWeibo.h"
#import <Twitter/Twitter.h>
#import "Definition.h"
#import <Accounts/Accounts.h>

@implementation WeiboShareManager

static WeiboShareManager *manager = nil;

- (id)init
{
    self = [super init];
    if (self) {
    }
    return self;
}

- (void)loginSina
{
    sinaweibo = [[SinaWeibo alloc] initWithAppKey:kAppKey appSecret:kAppSecret appRedirectURI:kAppRedirectURI andDelegate:self];
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSDictionary *sinaweiboInfo = [defaults objectForKey:@"SinaWeiboAuthData"];
    if ([sinaweiboInfo objectForKey:@"AccessTokenKey"] && [sinaweiboInfo objectForKey:@"ExpirationDateKey"] && [sinaweiboInfo objectForKey:@"UserIDKey"])
    {
        sinaweibo.accessToken = [sinaweiboInfo objectForKey:@"AccessTokenKey"];
        sinaweibo.expirationDate = [sinaweiboInfo objectForKey:@"ExpirationDateKey"];
        sinaweibo.userID = [sinaweiboInfo objectForKey:@"UserIDKey"];
    }
    [sinaweibo logIn];
}

- (void)dealloc
{
    NSLog(@"%s -> ", __FUNCTION__);
    sinaweibo.delegate = nil;
    [SinaWeibo release];
    [super dealloc];
}

#pragma mark - Weibo Delegate

- (void)sinaweiboDidLogIn:(SinaWeibo *)sinaweibo
{
    [self storeAuthData];
    //TODO share content on weibo
    [self SinaShareData:nil];
}

- (void)sinaweiboDidLogOut:(SinaWeibo *)sinaweibo
{
    [self removeAuthData];
    [manager release];
    manager = nil;
}

- (void)sinaweiboLogInDidCancel:(SinaWeibo *)sinaweibo
{}
- (void)sinaweibo:(SinaWeibo *)sinaweibo logInDidFailWithError:(NSError *)error
{}
- (void)sinaweibo:(SinaWeibo *)sinaweibo accessTokenInvalidOrExpired:(NSError *)error
{
    [self removeAuthData];
}

- (void)request:(SinaWeiboRequest *)request didReceiveResponse:(NSURLResponse *)response
{}
- (void)request:(SinaWeiboRequest *)request didReceiveRawData:(NSData *)data
{}
- (void)request:(SinaWeiboRequest *)request didFailWithError:(NSError *)error
{
    [self removeAuthData];
    [manager release];
    manager = nil;
}
- (void)request:(SinaWeiboRequest *)request didFinishLoadingWithResult:(id)result
{
    if ([request.url hasSuffix:@"statuses/upload.json"])
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"谢谢分享" message:nil delegate:nil cancelButtonTitle:@"不用客气" otherButtonTitles:nil];
        [alert show];
        [alert release];
        [manager release];
        manager = nil;
    }
    
    if ([request.url hasSuffix:@"friendships/create.json"]) {
        [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"beenfriendships"];
    }
}

- (void)storeAuthData
{
    NSDictionary *authData = [NSDictionary dictionaryWithObjectsAndKeys:
                              sinaweibo.accessToken, @"AccessTokenKey",
                              sinaweibo.expirationDate, @"ExpirationDateKey",
                              sinaweibo.userID, @"UserIDKey",
                              sinaweibo.refreshToken, @"refresh_token", nil];
    [[NSUserDefaults standardUserDefaults] setObject:authData forKey:@"SinaWeiboAuthData"];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

- (void)removeAuthData
{
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:@"SinaWeiboAuthData"];
}

- (void)SinaShareData:(NSString *)content
{
    [sinaweibo requestWithURL:@"statuses/upload.json"
                       params:[NSMutableDictionary dictionaryWithObjectsAndKeys:
                               kShareContent, @"status",
                               [UIImage imageNamed:@"Icon@2x.png"], @"pic", nil]
                   httpMethod:@"POST"
                     delegate:self];
    
    if (![[NSUserDefaults standardUserDefaults] boolForKey:@"beenfriendships"]) {
        [sinaweibo requestWithURL:@"friendships/create.json"
                           params:[NSMutableDictionary dictionaryWithObjectsAndKeys:@"_HalloWorld", @"screen_name", nil]
                       httpMethod:@"POST"
                         delegate:self];
    }
}

+ (void)LoginAndShareSina
{
    if (manager == nil) {
        manager = [[WeiboShareManager alloc] init];
    }
    [manager loginSina];
}

+ (void)LoginAndShareTwitter
{
    [[NSNotificationCenter defaultCenter] postNotificationName:@"shareTweeter" object:nil];
}

@end