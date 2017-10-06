//
//  ViewController.m
//  testluc1
//
//  Created by Brice Rosenzweig on 06/06/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UILabel *label;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (IBAction)buttonPressed:(id)sender {
    int foo = 19;
    void* bar = 0xffffffff;
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)pressMe:(id)sender {
    self.label.text = @"I am SOOO SMART";
    
}

@end
