//
//  ViewController.swift
//  SwiftAndCpp
//
//  Created by Brice Rosenzweig on 05/08/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        NSLog("YO: %lf", c_compute(3.0))
        
        let a = "Hello World"
        
        let n = c_size(UnsafePointer(a.cString(using: String.Encoding.utf8)));
        NSLog("YA: %d", n);
        
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

