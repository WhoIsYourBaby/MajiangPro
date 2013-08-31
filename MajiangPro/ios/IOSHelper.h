//
//  IOSHelper.h
//  MaJiong
//
//  Created by HalloWorld on 13-1-4.
//
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>

@interface IOSHelper : NSObject <SKProductsRequestDelegate, SKPaymentTransactionObserver, UIAlertViewDelegate>


+ (id)shareInterface;
+(void)buyNoIad;

@end
