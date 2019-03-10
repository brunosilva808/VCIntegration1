#import "VCIntegration.h"

@implementation VCIntegration

- (void)show:(CDVInvokedUrlCommand*)command
{

    NSString* name = [[command arguments] objectAtIndex:0];
    NSString* msg = [NSString stringWithFormat: @"Hello, %@", name];

    CDVPluginResult* result = [CDVPluginResult
                               resultWithStatus:CDVCommandStatus_OK
                               messageAsString:msg];



    [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];
}

@end
