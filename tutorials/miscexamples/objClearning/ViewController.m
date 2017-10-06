//
//  ViewController.m
//  objClearning
//
//  Created by Brice Rosenzweig on 14/08/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UILabel *myLabel;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}
- (IBAction)buttonPressed:(id)sender {
    NSLog(@"called button press function");
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
