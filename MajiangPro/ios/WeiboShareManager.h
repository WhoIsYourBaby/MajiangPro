//
//  WeiboShareManager.h
//  MaJiong
//
//  Created by Kira on 8/1/13.
//
//

#import <Foundation/Foundation.h>


#define kAppKey             @"1398129440"
#define kAppSecret          @"c9686249d21044ba39d25a05f475327e"
#define kAppRedirectURI     @"https://api.weibo.com/oauth2/default.html"

#ifndef kAppKey
#error
#endif

#ifndef kAppSecret
#error
#endif

#ifndef kAppRedirectURI
#error
#endif

#import "SinaWeibo.h"

@interface WeiboShareManager : NSObject <SinaWeiboDelegate, SinaWeiboRequestDelegate>
{
    SinaWeibo *sinaweibo;
}

+ (void)LoginAndShareSina;

+ (void)LoginAndShareTwitter;

@end