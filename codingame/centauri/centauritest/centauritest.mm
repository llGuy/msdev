//
//  centauritest.m
//  centauritest
//
//  Created by Brice Rosenzweig on 21/01/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "Message.hpp"
#import <cstdlib>
#import "Charles.hpp"

@interface centauritest : XCTestCase

@end

@implementation centauritest

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

-(void)testMatrixOp{
    vector<Message> M;
    Message one(32);
    one = 0b101100;
    M.push_back(one);
    one = 0b101010;
    M.push_back(one);
    one.swap_cols(M, 1, 2);
    
    XCTAssert(M[0] == 0b101010);
    XCTAssert(M[1] == 0b101100);
    
    one.factor_out_col(M, 1);
    
    cout << M[0] << endl;
    cout << M[1] << endl;
    XCTAssert(M[0]==0b110);
    XCTAssert(M[1]==0b101100);
    
}

-(void)testBasics32{
    Message input(32, (unsigned int[]) {0xb0c152f9,0xebf2831f});
    Message a(32, (unsigned int[]) {0xb0c152f9,0x0});
    Message b(32, (unsigned int[]) {0xebf2831f,0x0});
    
    Message x(32, (unsigned int[]) {0x3F7E, 0x0});
    Message y(32, (unsigned int[]) {0x11B, 0x0});
    
    Message output(32, (unsigned int[]) {0x46508fb7, 0x6677e201});
    Message simple(32, (unsigned int[]) {0b10000000000000000000000000001101, 0b10000000000000000000000000000001});
    
    Message step(32);
    
    XCTAssert(input.encode() == a*b);
    
    //XCTAssert(((simple << 3) >> 3) == simple);
    simple.debug_print();
    cout << dec;
    cout << simple << endl;
    cout << (simple << 3 ) << endl;
    cout << (((simple << 3 ) >> 2) >>2) << endl;
    
    XCTAssert(x%y == 1);
    XCTAssert(( (x/y) * y + (x%y) ) == x);
    
    // degenerate cases
    x = 0b10101;
    y = 0b101;
    XCTAssert(x%y == 1);
    XCTAssert(x/y == 0b100);
    
    x = 1;
    y = 1;
    XCTAssert(x%y == 0);
    XCTAssert(x/y == 1);
    
    x = 0;
    y = 1;
    XCTAssert(x%y == 0);
    XCTAssert(x/y == 0);

}

-(void)testDistinctDegree{
    Message a(32);
    a = 0b1001001;
    cout << a << endl;
    vector<Message> v = a.distinct_degree_factors();
    cout << v.size() << endl;
}

-(void)test32{
    //unsigned int b[2] = {0xb0c152f9,0xebf2831f};
    Message m(32,(unsigned int[]){0x46508fb7, 0x6677e201});
    Message a(32, (unsigned int[]) {0xb0c152f9,0x0});
    Message b(32, (unsigned int[]) {0xebf2831f,0x0});
    
    /*
     m = 0x73AF;
     a = 0x83;
     b = 0xE5;
     */
    
    vector<Message> rv = m.decode();
    for (size_t i=0; i<rv.size(); i++) {
        cout << hex << rv[i] << endl;
    }
    
    XCTAssertTrue(find(rv.begin(), rv.end(), Message(a,b)) != rv.end());
    
    
}


-(void)test64{
    Message ab(64, (unsigned int[]){0xf3268b49, 0x661859eb, 0x0b324559, 0x65ee6bda});
    Message a(64, (unsigned int[]){0x0cf5c2bf, 0x9aba68ef,0x0,0x0});
    Message b(64, (unsigned int[]){0xc18fb79b, 0xde70eef7,0x0,0x0});

    /*
    cout << dec;
    cout << ab << endl;
    cout << a*b << endl;
    cout << a << endl;
    cout << ab/b << endl;
     */
    XCTAssert( ab/b == a);
    XCTAssert( a*b == ab);
    
    cout << hex << ab << endl;
    vector<Message> rv = ab.decode();
    XCTAssertTrue(find(rv.begin(), rv.end(), Message(a,b)) != rv.end());

    
}

-(void)test128{
    Message ab(128);
    Message b(128);
    Message a(128);
    

    ab.read("a91db473 fcea8db4 f3bb434a 8dba2f16 51abc87e 92c44759 5c1a16d3 6111c6f4");
    a.read( "a30d28bd bda19675 3f95d074 b6f69434 00000000 00000000 00000000 00000000");
    b.read( "c58f4047 d73fe36a 24be2846 e2ebe432 00000000 00000000 00000000 00000000");
    cout << hex << a*b << endl;
    cout << hex << ab << endl;
    cout << hex << a << endl;
    cout << hex << b << endl;
    XCTAssert(a*b == ab);
    vector<Message> solution( ab.decode() );
    XCTAssertTrue(find(solution.begin(), solution.end(), Message(a,b)) != solution.end());
    
    ab.read("541a4231 5d324646 27219a26 12497b0e 724eddcb 0e131617 9521bedf 55544dc7");
    solution = ab.decode();
    for(size_t i=0;i<solution.size();i++){
        cout << solution[i] << endl;
    }
}

-(void)test256{
    //320a18d5 b61b13f6 1aaaa61c 0afe2a41 1a4ff107 84cc2efc 956ff31d fa595299 33749a7f 6cc9659d dc503569 ef4d0ef5 73b746c5 b8fb36d3 7616e9d6 b21251c4
    //33749a7f 6cc9659d dc503569 ef4d0ef5 73b746c5 b8fb36d3 7616e9d6 b21251c4 320a18d5 b61b13f6 1aaaa61c 0afe2a41 1a4ff107 84cc2efc 956ff31d fa595299
    Message ab(256);
    Message b(256);
    Message a(256);
    ab.read("4af6fc33 39029380 465c5267 c72f6a8b 0906e6d0 ca60550f 14a5e47c 42ad10fb 4a3bb446 bb74360a 5ea02b9c 23c68553 3fade253 e270ba24 39e141ad 6c38c43d");
    a.read( "33749a7f 6cc9659d dc503569 ef4d0ef5 73b746c5 b8fb36d3 7616e9d6 b21251c4 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000");
    b.read( "320a18d5 b61b13f6 1aaaa61c 0afe2a41 1a4ff107 84cc2efc 956ff31d fa595299 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000");
    XCTAssert(a*b == ab);
    int n = 1;
    
    vector<Message> solution( ab.decode() );
    XCTAssertTrue(find(solution.begin(), solution.end(), Message(a,b)) != solution.end());

    clock_t t0 = clock();
    for( int i =0 ;i<n; i++){
        ab.decode();
    }
    std::cerr << "m time: " << float(clock()-t0)/CLOCKS_PER_SEC/n << " second(s)\n";
    
    t0 = clock();
    for( int i =0 ;i<n; i++){
        decrypt(256, "4af6fc33 39029380 465c5267 c72f6a8b 0906e6d0 ca60550f 14a5e47c 42ad10fb 4a3bb446 bb74360a 5ea02b9c 23c68553 3fade253 e270ba24 39e141ad 6c38c43d");
    }
    std::cerr << "c time: " << float(clock()-t0)/CLOCKS_PER_SEC/n << " second(s)\n";

}

-(void)testMcElieceSample{
    Message a(32, (unsigned int[])  {0b100111111110110011, 0b00000000000000000000000000000000});
    Message ap(32, (unsigned int[]) {0b010001010101010001, 0b00000000000000000000000000000000});
    
    cout << a<< endl;
    cout << a.derivative() << endl;
    XCTAssertTrue(a.derivative() == ap);
    
    
}

- (void)testDerivative {
    XCTAssert(true);
    Message m(32);
    XCTAssert(m == 0);
    
    Message a(32, (unsigned int[]) {0b00000000000000000000000000010001, 0b00000000000000000000000000000000});
    Message b(32, (unsigned int[]) {0b00000000000000000000000000011011, 0b00000000000000000000000000000000});
    Message g(32, (unsigned int[]) {0b00000000000000000000000000000101, 0b00000000000000000000000000000000});
    //Message in(32, (unsigned int[]) {0x53000000, 0xCA000000});
    /*
    cout << g << endl;
    cout << a.gcd(b) << endl;
    
    cout << b << endl;
    cout << b.derivative() << endl;
     */
    XCTAssert(b.derivative() == 0b101);
    XCTAssert(a.gcd(b) == 0b101);
    
}

-(void)testRandom{
    Message m(32);
    
    cout << m.random(6) << endl;
    cout << m.random(48) << endl;
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
