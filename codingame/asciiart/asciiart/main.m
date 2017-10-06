//
//  main.m
//  asciiart
//
//  Created by Brice Rosenzweig on 08/01/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#import <Foundation/Foundation.h>

/*
 #  ##   ## ##  ### ###  ## # # ###  ## # # #   # # ###  #  ##   #  ##   ## ### # # # # # # # # # # ### ### \
# # # # #   # # #   #   #   # #  #    # # # #   ### # # # # # # # # # # #    #  # # # # # # # # # #   #   # \
### ##  #   # # ##  ##  # # ###  #    # ##  #   ### # # # # ##  # # ##   #   #  # # # # ###  #   #   #   ## \
# # # # #   # # #   #   # # # #  #  # # # # #   # # # # # # #    ## # #   #  #  # # # # ### # #  #  #       \
# # ##   ## ##  ### #    ## # # ###  #  # # ### # # # #  #  #     # # # ##   #  ###  #  # # # #  #  ###  #  \
";
 */


void solve(int L, int H, NSString * T, NSArray * art){
    const char * buf = [[T uppercaseString] UTF8String];

    NSMutableArray * solution = [NSMutableArray arrayWithCapacity:art.count];
    for (NSUInteger i=0; i<H; i++) {
        [solution addObject:[NSMutableString string]];
    }
    
    while( *buf != '\0'){
        char letter = buf[0];
        NSUInteger index = MIN( letter - 'A' >= 0 ? letter - 'A' : 26, 26);
        
        for (NSUInteger i=0; i<H; i++) {
            NSMutableString * line = solution[i];
            NSString * artline = art[i];
            
            NSString * element = [artline substringWithRange:NSMakeRange(index * L, L) ];
            [line appendString:element];
        }
        
        buf++;
    }
    for (NSString * line in solution) {
        printf("%s\n", [line UTF8String]);
    }
}

int main(int argc, const char * argv[]) {
    NSArray * art = @[
                      @" #  ##   ## ##  ### ###  ## # # ###  ## # # #   # # ###  #  ##   #  ##   ## ### # # # # # # # # # # ### ###",
                      @"# # # # #   # # #   #   #   # #  #    # # # #   ### # # # # # # # # # # #    #  # # # # # # # # # #   #   #",
                      @"### ##  #   # # ##  ##  # # ###  #    # ##  #   ### # # # # ##  # # ##   #   #  # # # # ###  #   #   #   ##",
                      @"# # # # #   # # #   #   # # # #  #  # # # # #   # # # # # # #    ## # #   #  #  # # # # ### # #  #  #      ",
                      @"# # ##   ## ##  ### #    ## # # ###  #  # # ### # # # #  #  #     # # # ##   #  ###  #  # # # #  #  ###  # ",
                      ];
    solve(4, 5, @"@AN@ATTAN", art);
    /*
    int L;
    scanf("%d", &L);
    int H;
    scanf("%d", &H); fgetc(stdin);
    char T[256];
    gets(T);
    NSMutableArray * art = [NSMutableArray array];
    for (int i = 0; i < H; i++) {
        char ROW[1024];
        gets(ROW);
        [art addObject:[NSString stringWithUTF8String:ROW]];
    }

    solve(L, H, [NSString stringWithUTF8String:T], art);
    */
    // Write an action using printf(). DON'T FORGET THE TRAILING NEWLINE \n
    // To debug: fprintf(stderr, [@"Debug messages\n" UTF8String]);
    
    return 0;
}
