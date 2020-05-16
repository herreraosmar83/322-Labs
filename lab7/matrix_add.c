#include <stdio.h>

int main(int argc, char* argv[]){

    printf("This lab is hard");
}


// The general layout for the matrix_add is provided below.  Note that within this code the read and write of each operation is performed asynchronously.  Within this code layout, you don’t receive any benefit from using asynchronous I/O.  


// matrix_add: block, size, scalar

// for i = 1 .. size 
//     for j = 1 .. size 
//                block[i][j] += scalar;
//      end for
// end for

// main: size, blocks

// start_time  = get current time;
// scalar        = random number;
// block_size = size / blocks;

// for x = 1 .. blocks
//    for y = 1 .. blocks
//        async read request matrix[x, y]
//        block = async read return matrix[x, y]
//        matrix_add(block, block_size, scaler)
//        async write request block
//        async write return block
//    end for
// end for

// 	end_time = get the current time
// emit end_time - start_time

// Once you have your programming working with the above code layout, you should enhance your project to move the asynchronous request and return calls further apart.   (Note that you can collapse the x & y loop into one, so that the program layout conforms to the revised layout with asynchronous operations. This means that your block size will be 1 x (“block_size” * “block_size”).  To effectively perform this step, you should consider operating in a pipeline fashion.  Within the pipeline, you will have three (3) blocks that are being managed by your program.
// last:  the last block that was processed and now needs to be written to the filesystem
// current:  the current block being processed by the matrix_add procedure
// next: the next block to be read in from the input file.

// You can both pipeline the read operation and the write operation.  To reduce confusion, the following layout provides you with the operation semantics of only performing the read operation in a pipeline fashion.


// /* First prime the pump by reading the first block */

// async read request current
// async read return current

// for current = 0 .. ( (block_size * block_size ) - 2)   {
// /* Note the blocks are number zero relative */
// last = current - 1;
// next - current + 1;

// async read request next                               /* see aio_read(2)    */

// matrix_add(current, block_size, scalar)

// async write request last                                /* see aio_write(2)   */
// async write return last                                   /* see aio_return(2) */
//      memcpy current → last                            /* see memcpy(3)    */

// async read return next                                  /* see aio_return(2) */
//      memcpy next → current



// /* Last drain the pump by handling the last block */

// matrix_add(current, block_size, scalar)
// async write request last
// async write return last

// To get further performance improvements, you can move the “async write return” call to the end of the loop.  Greater performance improvements -- at the cost of code clarity -- can be achieved by pipeline this call.

// Running some tests:
// Now that your program works, you can execute it with various block sizes.  First, obtain the size of a page and the maximum range of integer.  Based upon this information, you can calculate the number of integers per page.

// $ getconf PAGE_SIZE
// 4096
// $ getconf UINT_MAX
// 4294967295
// 2^32  = 4294967295 
// 32 / 8 = 4 bytes per integer

// 	4096 / 4 = 1024 integers per page. (1K)

// Now run your program with various block sizes, and you will see the performance impact on demand paging.  Here I have selected a matrix size of 10K x 10K (10240 x 10240)

// 	$  matrix_add 10240  20 < matrix_file.size-1 > matrix_file.size-2
// # hence block is ½ a page
// 	$  matrix_add 10240  10 < matrix_file.size-1 > matrix_file.size-2
// 		# hence a block is 1 page
// 	$  matrix_add 10240    5 < matrix_file.size-1 > matrix_file.size-2
// 		# hence a block is 2 pages
// 	$  matrix_add 10240    2 < matrix_file.size-1 > matrix_file.size-2
// 		# hence a block is 5 pages