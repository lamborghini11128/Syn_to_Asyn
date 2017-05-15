
module AND_async (A_0, A_1, B_0, B_1, Y_0, Y_1);
    input  A_0, A_1, B_0, B_1;
    output Y_0, Y_1;
    wire y0, y1, c_a, c_b, C;

    or  u1 (y0, A_0, B_0);
    and u2 (y1, A_1, B_1);
    or  u3 (c_a, A_0, A_1);
    or  u4 (c_b, B_0, B_1);
    and u5 (C, c_a, c_b);
    and u6 (Y_1, y1, C);
    and u7 (Y_0, y0, C);
endmodule

module NAND_async (A_0, A_1, B_0, B_1, Y_0, Y_1);
    input  A_0, A_1, B_0, B_1;
    output Y_0, Y_1;
    wire y0, y1, c_a, c_b, C;

    or  u1 (y0, A_0, B_0);
    and u2 (y1, A_1, B_1);
    or  u3 (c_a, A_0, A_1);
    or  u4 (c_b, B_0, B_1);
    and u5 (C, c_a, c_b);
    and u6 (Y_1, y0, C);
    and u7 (Y_0, y1, C);
endmodule

module ANDB_async (AN_0, AN_1, B_0, B_1, Y_0, Y_1);
    input  AN_0, AN_1, B_0, B_1;
    output Y_0, Y_1;
    wire y0, y1, c_a, c_b, C;

    or  u1 (y0, AN_1, B_0);
    and u2 (y1, AN_0, B_1);
    or  u3 (c_a, AN_0, AN_1);
    or  u4 (c_b, B_0, B_1);
    and u5 (C, c_a, c_b);
    and u6 (Y_1, y1, C);
    and u7 (Y_0, y0, C);
endmodule

module NANDB_async (AN_0, AN_1, B_0, B_1, Y_0, Y_1);
    input  AN_0, AN_1, B_0, B_1;
    output Y_0, Y_1;
    wire y0, y1, c_a, c_b, C;

    or  u1 (y0, AN_1, B_0);
    and u2 (y1, AN_0, B_1);
    or  u3 (c_a, AN_0, AN_1);
    or  u4 (c_b, B_0, B_1);
    and u5 (C, c_a, c_b);
    and u6 (Y_1, y0, C);
    and u7 (Y_0, y1, C);
endmodule

module ANDBB_async (AN_0, AN_1, BN_0, BN_1, Y_0, Y_1);
    input  AN_0, AN_1, BN_0, BN_1;
    output Y_0, Y_1;
    wire y0, y1, c_a, c_b, C;

    or  u1 (y0, AN_1, BN_1);
    and u2 (y1, AN_0, BN_0);
    or  u3 (c_a, AN_0, AN_1);
    or  u4 (c_b, BN_0, BN_1);
    and u5 (C, c_a, c_b);
    and u6 (Y_1, y1, C);
    and u7 (Y_0, y0, C);
endmodule


module OR_async ( A_0, A_1, B_0, B_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    input   B_0;
    input   B_1;
    output  Y_0;
    output  Y_1;
    wire    onset;
    wire    offset; 
    wire    c_0;
    wire    c_1;
    wire    complete;


    //onset 
    or  or1 ( onset, A_1, B_1);    
    //offset
    and and1( offset, A_0, B_0 );
    //complete detection
    or  or2 ( c_0, A_0, A_1 );
    or  or3 ( c_1, B_0, B_1 );
    and and2( complete, c_0, c_1);
    //output
    and and3( Y_0, complete, offset );
    and and4( Y_1, complete, onset  );

    //  A  B  Y  
    //  0  0  0
    //  X  1  1
    //  1  x  1
endmodule

module ORB_async ( AN_0, AN_1, B_0, B_1, Y_0, Y_1);
    input   AN_0;
    input   AN_1;
    input   B_0;
    input   B_1;
    output  Y_0;
    output  Y_1;
    wire    onset;
    wire    offset; 
    wire    c_0;
    wire    c_1;
    wire    complete;


    //onset 
    or  or1 ( onset, AN_0, B_1);    
    //offset
    and and1( offset, AN_1, B_0 );
    //complete detection
    or  or2 ( c_0, AN_0, AN_1 );
    or  or3 ( c_1, B_0, B_1 );
    and and2( complete, c_0, c_1);
    //output
    and and3( Y_0, complete, offset );
    and and4( Y_1, complete, onset  );

    //  A  B  Y  
    //  0  0  0
    //  X  1  1
    //  1  x  1
endmodule

module ORBB_async ( AN_0, AN_1, BN_0, BN_1, Y_0, Y_1);
    input   AN_0;
    input   AN_1;
    input   BN_0;
    input   BN_1;
    output  Y_0;
    output  Y_1;
    wire    onset;
    wire    offset; 
    wire    c_0;
    wire    c_1;
    wire    complete;


    //onset 
    or  or1 ( onset, AN_0, BN_0);    
    //offset
    and and1( offset, AN_1, BN_1 );
    //complete detection
    or  or2 ( c_0, AN_0, AN_1 );
    or  or3 ( c_1, BN_0, BN_1 );
    and and2( complete, c_0, c_1);
    //output
    and and3( Y_0, complete, offset );
    and and4( Y_1, complete, onset  );

    //  A  B  Y  
    //  0  0  0
    //  X  1  1
    //  1  x  1
endmodule

module NOR_async ( A_0, A_1, B_0, B_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    input   B_0;
    input   B_1;
    output  Y_0;
    output  Y_1;
    wire    onset;
    wire    offset; 
    wire    c_0;
    wire    c_1;
    wire    complete;


    //onset 
    and and1( onset, A_0, B_0 );
    //offset
    or  or1 ( offset, A_1, B_1);   
    //complete detection
    or  or2 ( c_0, A_0, A_1 );
    or  or3 ( c_1, B_0, B_1 );
    and and2( complete, c_0, c_1);
    //output
    and and3( Y_0, complete, offset );
    and and4( Y_1, complete, onset  );

    //  A  B  Y  
    //  0  0  0
    //  X  1  1
    //  1  x  1
endmodule

module NORB_async ( AN_0, AN_1, B_0, B_1, Y_0, Y_1);
    input   AN_0;
    input   AN_1;
    input   B_0;
    input   B_1;
    output  Y_0;
    output  Y_1;
    wire    onset;
    wire    offset; 
    wire    c_0;
    wire    c_1;
    wire    complete;


    //onset 
    and and1( onset, AN_1, B_0 );
    //offset
    or  or1 ( offset, AN_0, B_1);   
    //complete detection
    or  or2 ( c_0, AN_0, AN_1 );
    or  or3 ( c_1, B_0, B_1 );
    and and2( complete, c_0, c_1);
    //output
    and and3( Y_0, complete, offset );
    and and4( Y_1, complete, onset  );

    //  A  B  Y  
    //  1  0  0
    //  X  1  1
    //  0  x  1
endmodule




module INV_async (A_0, A_1, Y_0, Y_1);
    input  A_0, A_1;
    output Y_0, Y_1;

    assign Y_0 = A_1;
    assign Y_1 = A_0;

    /*
    //onset 
    assign onset = A_0;
    //offset
    assign offset = A_1;
    //complete detection
    or complete1 ( complete, A_0, A_1);

    //output
    and and3( Y_0, complete, offset );
    and and4( Y_1, complete, onset  );
    */
    //  A  Y  
    //  0  1
    //  1  0

endmodule

module BUF_async (A_0, A_1, Y_0, Y_1);
    input  A_0, A_1;
    output Y_0, Y_1;

    wire    onset;
    wire    offset; 
    wire    c_0;
    wire    c_1;
    wire    complete;
    assign Y_0 = A_0;
    assign Y_1 = A_1;

/*
    //onset 
    assign onset = A_1;
    //offset
    assign offset = A_0;
    //complete detection
    or complete1 ( complete, A_0, A_1);

    //output
    and and3( Y_0, complete, offset );
    and and4( Y_1, complete, onset  );
*/
    //  A  Y  
    //  0  1
    //  1  0

endmodule

module XOR_async ( A_0, A_1, B_0, B_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    input   B_0;
    input   B_1;
    output  Y_0;
    output  Y_1;
/*
    assign Y_0 = ( A_0 == A_1 || B_0 == B_1 )? 1'b0 : ~(A_1 ^ B_1); 
    assign Y_1 = ( A_0 == A_1 || B_0 == B_1 )? 1'b0 : A_1 ^ B_1;
*/
    
	AND_async u1( A_0, A_1, B_1, B_0, S_0, S_1); 
    AND_async u2( A_1, A_0, B_0, B_1, T_0, T_1);
    OR_async  u3( S_0, S_1, T_0, T_1, Y_0, Y_1);
    
	
endmodule


module TBUF_async (A_0, A_1, S_0, S_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    input   S_0;
    input   S_1;
    output  Y_0;
    output  Y_1;

    reg     T_0, T_1;
    always@(*) begin
        if( S_0 != S_1 && S_1 ) begin
            T_0 = A_0;
            T_1 = A_1;
        end 
        else begin
            T_0 = 1'b0;
            T_1 = 1'b0;
        end

    end

    assign Y_0 = T_0;
    assign Y_1 = T_1;

endmodule 


////////////////////////////////////////////////////////////////////////////////

module ADDHXL_async (A_0, A_1, B_0, B_1, CO_0, CO_1, S_0, S_1);
    input  A_0, A_1, B_0, B_1;
    output CO_0, CO_1, S_0, S_1;

    AND_async u1( A_0, A_1, B_0, B_1, CO_0, CO_1 );
    XOR_async u2( A_0, A_1, B_0, B_1, S_0, S_1);


endmodule


module AND2X1_async (A_0, A_1, B_0, B_1, Y_0, Y_1);
    input A_0, A_1, B_0, B_1;
    output Y_0, Y_1;
    
    AND_async u1( A_0, A_1, B_0, B_1, Y_0, Y_1 );

endmodule

module AND2X2_async (A_0, A_1, B_0, B_1, Y_0, Y_1);
    input A_0, A_1, B_0, B_1;
    output Y_0, Y_1;
    
    AND_async u1( A_0, A_1, B_0, B_1, Y_0, Y_1 );

endmodule

module AND3X2_async (A_0, A_1, B_0, B_1, C_0, C_1, Y_0, Y_1);
    input A_0, A_1, B_0, B_1, C_0, C_1;
    output Y_0, Y_1;
    
    AND_async u1( A_0, A_1, B_0, B_1, S_0, S_1 );
    AND_async u2( S_0, S_1, C_0, C_1, Y_0, Y_1 );

endmodule

module AND3X1_async (A_0, A_1, B_0, B_1, C_0, C_1, Y_0, Y_1);
    input A_0, A_1, B_0, B_1, C_0, C_1;
    output Y_0, Y_1;
    
    AND_async u1( A_0, A_1, B_0, B_1, S_0, S_1 );
    AND_async u2( S_0, S_1, C_0, C_1, Y_0, Y_1 );

endmodule

module AND4X1_async (A_0, A_1, B_0, B_1, C_0, C_1, D_0, D_1, Y_0, Y_1);
    input A_0, A_1, B_0, B_1, C_0, C_1, D_0, D_1;
    output Y_0, Y_1;

    AND_async u1( A_0, A_1, B_0, B_1, S_0, S_1 );
    AND_async u2( C_0, C_1, D_0, D_1, T_0, T_1 );
    AND_async u3( S_0, S_1, T_0, T_1, Y_0, Y_1 );

endmodule

module AO21X1_async (A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, Y_0, Y_1);
    input A0_0, A0_1, A1_0, A1_1, B0_0, B0_1;
    output Y_0, Y_1;

    AND_async u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1 );
    OR_async  u2( S_0,  S_1,  B0_0, B0_1, Y_0, Y_1 );

endmodule

module AOI211X1_async (A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, C0_0, C0_1, Y_0, Y_1);
    input A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, C0_0, C0_1;
    output Y_0, Y_1;

    AND_async u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1 );
    OR_async  u2( B0_0, B0_1, C0_0, C0_1, T_0, T_1 );
    OR_async  u3( S_0,  S_1,  T_0,  T_1,  Y_1, Y_0 );

endmodule

module AOI21X1_async (A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, Y_0, Y_1);
    input A0_0, A0_1, A1_0, A1_1, B0_0, B0_1;
    output Y_0, Y_1;

    AND_async u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1 );
    OR_async u2( S_0,  S_1,  B0_0, B0_1, Y_1, Y_0 );

endmodule

module AOI22X1_async (A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, B1_0, B1_1, Y_0, Y_1);
    input A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, B1_0, B1_1;
    output Y_0, Y_1;

    AND_async u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1 );
    AND_async u2( B0_0, B0_1, B1_0, B1_1, T_0, T_1 );
    OR_async u3( S_0,  S_1,  T_0, T_1, Y_1, Y_0 );

endmodule

module AOI21XL_async (A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, Y_0, Y_1);
    input A0_0, A0_1, A1_0, A1_1, B0_0, B0_1;
    output Y_0, Y_1;

    AND_async u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1 );
    OR_async u2( S_0,  S_1,  B0_0, B0_1, Y_1, Y_0 );

endmodule

module AOI221XL_async (A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, B1_0, B1_1, C0_0, C0_1, Y_0, Y_1);
    input A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, B1_0, B1_1, C0_0, C0_1;
    output Y_0, Y_1;

    AND_async u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1 );
    AND_async u2( B0_0, B0_1, B1_0, B1_1, T_0, T_1 );
    OR_async  u3( S_0,  S_1,  T_0,  T_1,  U_0, U_1 );
    OR_async u4( U_0,  U_1,  C0_0, C0_1, Y_1, Y_0 );

endmodule

module AOI222XL_async (A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, B1_0, B1_1, C0_0, C0_1, C1_0, C1_1, Y_0, Y_1);
    input A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, B1_0, B1_1, C0_0, C0_1, C1_0, C1_1;
    output Y_0, Y_1;

    AND_async u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1 );
    AND_async u2( B0_0, B0_1, B1_0, B1_1, T_0, T_1 );
    AND_async u3( C0_0, C0_1, C1_0, C1_1, U_0, U_1 );
    OR_async  u4( S_0,  S_1,  T_0,  T_1,  W_0, W_1 );
    OR_async u5( U_0,  U_1,  W_0,  W_1,  Y_1, Y_0 );

endmodule

module AO22X1_async (A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, B1_0, B1_1, Y_0, Y_1);
    input A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, B1_0, B1_1;
    output Y_0, Y_1;

    AND_async u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1 );
    AND_async u2( B0_0, B0_1, B1_0, B1_1, T_0, T_1 );
    OR_async  u3( S_0,  S_1,  T_0,  T_1,  Y_0, Y_1 );

endmodule

module AOI22XL_async (A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, B1_0, B1_1, Y_0, Y_1);
    input A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, B1_0, B1_1;
    output Y_0, Y_1;

    AND_async u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1 );
    AND_async u2( B0_0, B0_1, B1_0, B1_1, T_0, T_1 );
    OR_async u3( S_0,  S_1,  T_0,  T_1,  Y_1, Y_0 );

endmodule

module AOI2B1X1_async (A0_0, A0_1, A1N_0, A1N_1, B0_0, B0_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1N_0;
    input   A1N_1;
    input   B0_0;
    input   B0_1;
    output  Y_0;
    output  Y_1;
    
    ANDB_async u1( A1N_0, A1N_1, A0_0, A0_1, S_0, S_1 );
    OR_async  u2( S_0,   S_1,   B0_0, B0_1, Y_1, Y_0 );
    // AOI2B1X1_async
    //  A0  A1N B0  Y  
    //  0   X   0   1
    //  X   1   0   1
    //  X   X   1   0
    //  1   0   X   0
endmodule

module AOI2BB1X1_async (A0N_0, A0N_1, A1N_0, A1N_1, B0_0, B0_1, Y_0, Y_1);
    input   A0N_0;
    input   A0N_1;
    input   A1N_0;
    input   A1N_1;
    input   B0_0;
    input   B0_1;
    output  Y_0;
    output  Y_1;

    ANDBB_async u1( A0N_0, A0N_1, A1N_0, A1N_1, S_0, S_1 );
    OR_async   u2( S_0,   S_1,   B0_0,  B0_1,  Y_1, Y_0 );

endmodule

module AOI2BB2X1_async (A0N_0, A0N_1, A1N_0, A1N_1, B0_0, B0_1, B1_0, B1_1, Y_0, Y_1);
    input   A0N_0;
    input   A0N_1;
    input   A1N_0;
    input   A1N_1;
    input   B0_0;
    input   B0_1;
    input   B1_0;
    input   B1_1;
    output  Y_0;
    output  Y_1;

    ANDBB_async u1( A0N_0, A0N_1, A1N_0, A1N_1, S_0, S_1 );
    AND_async   u2( B0_0,  B0_1,  B1_0,  B1_1,  T_0, T_1 );
    OR_async   u3( S_0,   S_1,   T_0,   T_1,   Y_1, Y_0 );

endmodule

module AOI31X1_async (A0_0, A0_1, A1_0, A1_1, A2_0, A2_1, B0_0, B0_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1_0;
    input   A1_1;
    input   A2_0;
    input   A2_1;
    input   B0_0;
    input   B0_1;
    output  Y_0;
    output  Y_1;

    AND_async u1 ( A0_0, A0_1, A1_0, A1_1, S_0, S_1 );
    AND_async u2 ( A2_0, A2_1, S_0,  S_1,  T_0, T_1 );
    OR_async u3 ( B0_0, B0_1, T_0,  T_1,  Y_1, Y_0 );

endmodule

module AOI32XL_async (A0_0, A0_1, A1_0, A1_1, A2_0, A2_1, B0_0, B0_1, B1_0, B1_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1_0;
    input   A1_1;
    input   A2_0;
    input   A2_1;
    input   B0_0;
    input   B0_1;
    input   B1_0;
    input   B1_1;
    output  Y_0;
    output  Y_1;

    AND_async u1 ( A0_0, A0_1, A1_0, A1_1, S_0, S_1 );
    AND_async u2 ( A2_0, A2_1, S_0,  S_1,  T_0, T_1 );
    AND_async u3 ( B0_0, B0_1, B1_0, B1_1, U_0, U_1 );
    OR_async u4 ( T_0,  T_1,  U_0,  U_1,  Y_1, Y_0 );

endmodule

module BUFX2_async ( A_0, A_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    output  Y_0;
    output  Y_1;

    assign Y_0 = A_0;
    assign Y_1 = A_1;

    // CLKBUFX2_async m( .AN_0(A_0), .AN_1(A_1), .B_0(B_0), .B_1(B_1), .Y_0(Y_0), .Y_1(Y_1) );
    //  A   Y  
    //  0   0
    //  1   1
endmodule

module CLKBUFX3_async ( A_0, A_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    output  Y_0;
    output  Y_1;

    assign Y_0 = A_0;
    assign Y_1 = A_1;

    // CLKBUFX2_async m( .AN_0(A_0), .AN_1(A_1), .B_0(B_0), .B_1(B_1), .Y_0(Y_0), .Y_1(Y_1) );
    //  A   Y  
    //  0   0
    //  1   1
endmodule


module CLKBUFX2_async ( A_0, A_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    output  Y_0;
    output  Y_1;

    BUF_async u1 ( A_0, A_1, Y_0, Y_1 );

    // CLKBUFX2_async m( .AN_0(A_0), .AN_1(A_1), .B_0(B_0), .B_1(B_1), .Y_0(Y_0), .Y_1(Y_1) );
    //  A   Y  
    //  0   0
    //  1   1
endmodule

module CLKINVX1_async ( A_0, A_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    output  Y_0;
    output  Y_1;

    INV_async u1( A_0, A_1, Y_0, Y_1 );

endmodule

module INVX1_async (A_0, A_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    output  Y_0;
    output  Y_1;

    INV_async u1( A_0, A_1, Y_0, Y_1 );

endmodule

module INVXL_async (A_0, A_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    output  Y_0;
    output  Y_1;

    INV_async u1( A_0, A_1, Y_0, Y_1 );

endmodule

module CLKNAND2X2_async ( A_0, A_1, B_0, B_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    input   B_0;
    input   B_1;
    output  Y_0;
    output  Y_1;
    
    AND_async u1( A_0, A_1, B_0, B_1, Y_1, Y_0 );

endmodule

module CLKXOR2X2_async (A_0, A_1, B_0, B_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    input   B_0;
    input   B_1;
    output  Y_0;
    output  Y_1;
    
    XOR_async u1( A_0, A_1, B_0, B_1, Y_0, Y_1);
/*
    OR_async   u1( A_0, A_1, B_0, B_1, S_0, S_1);
    AND_async u2( A_0, A_1, B_0, B_1, T_1, T_0);
    AND_async  u3( S_0, S_1, T_0, T_1, Y_0, Y_1);
    */

endmodule

module CLKMX2X2_async ( A_0, A_1, B_0, B_1, S0_0, S0_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    input   B_0;
    input   B_1;
    input   S0_0;
    input   S0_1;
    output  Y_0;
    output  Y_1;

    ANDB_async u1( S0_0, S0_1, A_0, A_1, T_0, T_1 );
    AND_async  u2( S0_0, S0_1, B_0, B_1, U_0, U_1 );
    OR_async   u3( T_0,  T_1,  U_0, U_1, Y_0, Y_1 );

    // MX2X1_async 
    //  S0 A  B   Y  
    //  0  0  X   0
    //  1  X  0   0
    //  0  1  X   1
    //  1  X  1   1
endmodule



module NAND2X1_async ( A_0, A_1, B_0, B_1, Y_0, Y_1 );
    input   A_0;
    input   A_1;
    input   B_0;
    input   B_1;
    output  Y_0;
    output  Y_1;
    
    AND_async u1( A_0, A_1, B_0, B_1, Y_1, Y_0 );

endmodule

module NAND2XL_async ( A_0, A_1, B_0, B_1, Y_0, Y_1 );
    input   A_0;
    input   A_1;
    input   B_0;
    input   B_1;
    output  Y_0;
    output  Y_1;
    
    AND_async u1( A_0, A_1, B_0, B_1, Y_1, Y_0 );
    
endmodule

module NAND3BX1_async ( AN_0, AN_1, B_0, B_1, C_0, C_1, Y_0, Y_1);
    input   AN_0, AN_1;
    input   B_0, B_1, C_0, C_1;
    output  Y_0;
    output  Y_1;

    AND_async u1( AN_1, AN_0, B_0, B_1, S_0, S_1 );
    AND_async u2(  S_0,  S_1, C_0, C_1, Y_1, Y_0 );
endmodule

module NAND3X1_async ( A_0, A_1, B_0, B_1, C_0, C_1, Y_0, Y_1);
    input   A_0, A_1;
    input   B_0, B_1, C_0, C_1;
    output  Y_0;
    output  Y_1;

    AND_async u1(  A_0,  A_1, B_0, B_1, S_0, S_1 );
    AND_async u2(  S_0,  S_1, C_0, C_1, Y_1, Y_0 );
endmodule

module NAND4X1_async (A_0, A_1, B_0, B_1, C_0, C_1, D_0, D_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    input   B_0;
    input   B_1;
    input   C_0;
    input   C_1;
    input   D_0;
    input   D_1;
    output  Y_0;
    output  Y_1;

    AND_async  u1( A_0, A_1, B_0, B_1, S_0, S_1 );
    AND_async  u2( C_0, C_1, D_0, D_1, T_0, T_1 );
    AND_async u3( S_0, S_1, T_0, T_1, Y_1, Y_0 );

endmodule

module NAND4BBXL_async ( AN_0, AN_1, BN_0, BN_1, C_0, C_1, D_0, D_1, Y_0, Y_1);
    input   AN_0;
    input   AN_1;
    input   BN_0;
    input   BN_1;
    input   C_0;
    input   C_1;
    input   D_0;
    input   D_1;
    output  Y_0;
    output  Y_1;

    AND_async  u1( AN_1, AN_0, BN_1, BN_0, S_0, S_1 );
    AND_async  u2( C_0, C_1, D_0, D_1, T_0, T_1 );
    AND_async  u3( S_0, S_1, T_0, T_1, Y_1, Y_0 );

endmodule


module MX2X1_async ( A_0, A_1, B_0, B_1, S0_0, S0_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    input   B_0;
    input   B_1;
    input   S0_0;
    input   S0_1;
    output  Y_0;
    output  Y_1;

    ANDB_async u1( S0_0, S0_1, A_0, A_1, T_0, T_1 );
    AND_async  u2( S0_0, S0_1, B_0, B_1, U_0, U_1 );
    OR_async   u3( T_0,  T_1,  U_0, U_1, Y_0, Y_1 );

    // MX2X1_async 
    //  S0 A  B   Y  
    //  0  0  X   0
    //  1  X  0   0
    //  0  1  X   1
    //  1  X  1   1
endmodule

module MX2XL_async (A_0, A_1, B_0, B_1, S0_0, S0_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    input   B_0;
    input   B_1;
    input   S0_0;
    input   S0_1;
    output  Y_0;
    output  Y_1;

    ANDB_async u1( S0_0, S0_1, A_0, A_1, T_0, T_1 );
    AND_async  u2( S0_0, S0_1, B_0, B_1, U_0, U_1 );
    OR_async   u3( T_0,  T_1,  U_0, U_1, Y_0, Y_1 );

endmodule

module MX4XL_async (A_0, A_1, B_0, B_1, C_0, C_1, D_0, D_1, S0_0, S0_1, S1_0, S1_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    input   B_0;
    input   B_1;
    input   C_0;
    input   C_1;
    input   D_0;
    input   D_1;
    input   S0_0;
    input   S0_1;
    input   S1_0;
    input   S1_1;
    output  Y_0;
    output  Y_1;

    ANDB_async u1( S0_0, S0_1, A_0,  A_1,  T0_0, T0_1 );
    AND_async  u2( S0_0, S0_1, B_0,  B_1,  U0_0, U0_1 );
    OR_async   u3( T0_0, T0_1, U0_0, U0_1, V0_0, V0_1 );

    ANDB_async u4( S0_0, S0_1, C_0,  C_1,  T1_0, T1_1 );
    AND_async  u5( S0_0, S0_1, D_0,  D_1,  U1_0, U1_1 );
    OR_async   u6( T1_0, T1_1, U1_0, U1_1, V1_0, V1_1 );

    ANDB_async u7( S1_0, S1_1, V0_0, V0_1, X0_0, X0_1 );
    AND_async  u8( S1_0, S1_1, V1_0, V1_1, X1_0, X1_1 );
    OR_async   u9( X0_0, X0_1, X1_0, X1_1, Y_0,  Y_1  );
    // MX4XL_async 
    //  S1 S0 A  B  C  D  Y  
    //  0  0  0  X  X  X  0
    //  0  0  1  X  X  X  1
    //  0  1  X  0  X  X  0
    //  0  1  X  1  X  X  1
    //  1  0  X  X  0  X  0
    //  1  0  X  X  1  X  1
    //  1  1  X  X  X  0  0
    //  1  1  X  X  X  1  1
endmodule

module MXI2X1_async ( A_0, A_1, B_0, B_1, S0_0, S0_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    input   B_0;
    input   B_1;
    input   S0_0;
    input   S0_1;
    output  Y_0;
    output  Y_1;
    
    ANDB_async u1( S0_0, S0_1, A_0, A_1, T_0, T_1 );
    AND_async  u2( S0_0, S0_1, B_0, B_1, U_0, U_1 );
    OR_async  u3( T_0,  T_1,  U_0, U_1, Y_1, Y_0 );

    // MXI2X1_async 
    //  S0 A  B   Y  
    //  0  0  X   1
    //  1  X  0   1
    //  0  1  X   0
    //  1  X  1   0
endmodule

module MXI2XL_async ( A_0, A_1, B_0, B_1, S0_0, S0_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    input   B_0;
    input   B_1;
    input   S0_0;
    input   S0_1;
    output  Y_0;
    output  Y_1;
    
    ANDB_async u1( S0_0, S0_1, A_0, A_1, T_0, T_1 );
    AND_async  u2( S0_0, S0_1, B_0, B_1, U_0, U_1 );
    OR_async  u3( T_0,  T_1,  U_0, U_1, Y_1, Y_0 );

endmodule

module NAND2BX1_async ( AN_0, AN_1, B_0, B_1, Y_0, Y_1);
    input   AN_0;
    input   AN_1;
    input   B_0;
    input   B_1;
    output  Y_0;
    output  Y_1;

    ANDB_async u1(AN_0, AN_1, B_0, B_1, Y_1, Y_0);

endmodule

module NAND4BX1_async ( AN_0, AN_1, B_0, B_1, C_0, C_1, D_0, D_1, Y_0, Y_1 );
    input   AN_0;
    input   AN_1;
    input   B_0;
    input   B_1;
    input   C_0;
    input   C_1;
    input   D_0;
    input   D_1;
    output  Y_0;
    output  Y_1;

    ANDB_async u1(AN_0, AN_1, B_0, B_1, S0_0, S0_1);
    AND_async  u2( C_0,  C_1, D_0, D_1, S1_0, S1_1);
    AND_async  u3( S0_0,  S0_1, S1_0, S1_1, Y_1, Y_0);
endmodule


module NOR2BX1_async ( AN_0, AN_1, B_0, B_1, Y_0, Y_1);
    input   AN_0;
    input   AN_1;
    input   B_0;
    input   B_1;
    output  Y_0;
    output  Y_1;

    ORB_async u1( AN_0, AN_1, B_0, B_1, Y_1, Y_0);

endmodule

module NOR2X1_async (A_0, A_1, B_0, B_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    input   B_0;
    input   B_1;
    output  Y_0;
    output  Y_1;

    OR_async u1( A_0, A_1, B_0, B_1, Y_1, Y_0);

endmodule

module NOR2XL_async (A_0, A_1, B_0, B_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    input   B_0;
    input   B_1;
    output  Y_0;
    output  Y_1;

    OR_async u1( A_0, A_1, B_0, B_1, Y_1, Y_0);

endmodule

module NOR3X1_async (A_0, A_1, B_0, B_1, C_0, C_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    input   B_0;
    input   B_1;
    input   C_0;
    input   C_1;
    output  Y_0;
    output  Y_1;

    OR_async  u1( A_0, A_1, B_0, B_1, S_0, S_1);
    OR_async u2( S_0, S_1, C_0, C_1, Y_1, Y_0);

endmodule

module NOR3BXL_async (AN_0, AN_1, B_0, B_1, C_0, C_1, Y_0, Y_1);
    input   AN_0;
    input   AN_1;
    input   B_0;
    input   B_1;
    input   C_0;
    input   C_1;
    output  Y_0;
    output  Y_1;

    OR_async  u1( AN_1, AN_0, B_0, B_1, S_0, S_1);
    OR_async  u2( S_0,  S_1,  C_0, C_1, Y_1, Y_0);

endmodule

module NOR4X1_async (A_0, A_1, B_0, B_1, C_0, C_1, D_0, D_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    input   B_0;
    input   B_1;
    input   C_0;
    input   C_1;
    input   D_0;
    input   D_1;
    output  Y_0;
    output  Y_1;
    
    OR_async  u1( A_0, A_1, B_0, B_1, S_0, S_1 );
    OR_async  u2( C_0, C_1, D_0, D_1, T_0, T_1 );
    OR_async u3( S_0, S_1, T_0, T_1, Y_1, Y_0);

endmodule

module NOR4BBX1_async (AN_0, AN_1, BN_0, BN_1, C_0, C_1, D_0, D_1, Y_0, Y_1);
    input   AN_0;
    input   AN_1;
    input   BN_0;
    input   BN_1;
    input   C_0;
    input   C_1;
    input   D_0;
    input   D_1;
    output  Y_0;
    output  Y_1;
    
    OR_async  u1( AN_1, AN_0, BN_1, BN_0, S_0, S_1 );
    OR_async  u2( C_0, C_1, D_0, D_1, T_0, T_1 );
    OR_async u3( S_0, S_1, T_0, T_1, Y_1, Y_0);

endmodule

module OA21XL_async (A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1_0;
    input   A1_1;
    input   B0_0;
    input   B0_1;
    output  Y_0;
    output  Y_1;

    OR_async  u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1);
    AND_async u3( S_0, S_1, B0_0, B0_1, Y_0, Y_1);


endmodule



module OA22X1_async (A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, B1_0, B1_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1_0;
    input   A1_1;
    input   B0_0;
    input   B0_1;
    input   B1_0;
    input   B1_1;
    output  Y_0;
    output  Y_1;

    OR_async  u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1);
    OR_async  u2( B0_0, B0_1, B1_0, B1_1, T_0, T_1);
    AND_async u3( S_0, S_1, T_0, T_1, Y_0, Y_1);


endmodule

module OAI211XL_async (A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, C0_0, C0_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1_0;
    input   A1_1;
    input   B0_0;
    input   B0_1;
    input   C0_0;
    input   C0_1;
    output  Y_0;
    output  Y_1;
    wire    onset;
    wire    offset; 
    wire    c_0, c_1, c_2, c_3;
    wire    on0, off0, off1;
    wire    complete;

    OR_async   u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1);
    AND_async  u2( B0_0, B0_1, C0_0, C0_1, T_0, T_1);
    AND_async u3( S_0, S_1, T_0, T_1, Y_1, Y_0);

endmodule

module OAI211X1_async (A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, C0_0, C0_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1_0;
    input   A1_1;
    input   B0_0;
    input   B0_1;
    input   C0_0;
    input   C0_1;
    output  Y_0;
    output  Y_1;
    wire    onset;
    wire    offset; 
    wire    c_0, c_1, c_2, c_3;
    wire    on0, off0, off1;
    wire    complete;

    OR_async   u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1);
    AND_async  u2( B0_0, B0_1, C0_0, C0_1, T_0, T_1);
    AND_async u3( S_0, S_1, T_0, T_1, Y_1, Y_0);

endmodule

module OAI21X1_async (A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1_0;
    input   A1_1;
    input   B0_0;
    input   B0_1;
    output  Y_0;
    output  Y_1;

    OR_async   u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1);
    AND_async u2( S_0, S_1, B0_0, B0_1, Y_1, Y_0);


endmodule

module OAI21XL_async (A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1_0;
    input   A1_1;
    input   B0_0;
    input   B0_1;
    output  Y_0;
    output  Y_1;

    OR_async   u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1);
    AND_async u2( S_0, S_1, B0_0, B0_1, Y_1, Y_0);


endmodule

module OAI21BX1_async (A0_0, A0_1, A1_0, A1_1, B0N_0, B0N_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1_0;
    input   A1_1;
    input   B0N_0;
    input   B0N_1;
    output  Y_0;
    output  Y_1;

    OR_async   u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1);
    ANDB_async u2( B0N_0, B0N_1, S_0, S_1, Y_1, Y_0);
endmodule

module OAI221X1_async (A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, B1_0, B1_1, C0_0, C0_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1_0;
    input   A1_1;
    input   B0_0;
    input   B0_1;
    input   B1_0;
    input   B1_1;
    input   C0_0;
    input   C0_1;
    output  Y_0;
    output  Y_1;

    OR_async   u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1);
    OR_async   u2( B0_0, B0_1, B1_0, B1_1, T_0, T_1);
    AND_async  u3( S_0, S_1, T_0, T_1, U_0, U_1);
    AND_async u4( U_0, U_1, C0_0, C0_1, Y_1, Y_0);


endmodule

module OAI221XL_async (A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, B1_0, B1_1, C0_0, C0_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1_0;
    input   A1_1;
    input   B0_0;
    input   B0_1;
    input   B1_0;
    input   B1_1;
    input   C0_0;
    input   C0_1;
    output  Y_0;
    output  Y_1;

    OR_async   u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1);
    OR_async   u2( B0_0, B0_1, B1_0, B1_1, T_0, T_1);
    AND_async  u3( S_0, S_1, T_0, T_1, U_0, U_1);
    AND_async u4( U_0, U_1, C0_0, C0_1, Y_1, Y_0);
endmodule

module OAI222X1_async (A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, B1_0, B1_1, C0_0, C0_1, C1_0, C1_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1_0;
    input   A1_1;
    input   B0_0;
    input   B0_1;
    input   B1_0;
    input   B1_1;
    input   C0_0;
    input   C0_1;
    input   C1_0;
    input   C1_1;
    output  Y_0;
    output  Y_1;
    wire    onset;
    wire    offset; 
    wire    c_0, c_1, c_2, c_3, c_4;
    wire    on0, on1, on2, off0, off1, off2, off3, off4, off5, off6, off7;
    wire    complete;

    OR_async   u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1);
    OR_async   u2( B0_0, B0_1, B1_0, B1_1, T_0, T_1);
    OR_async   u3( C0_0, C0_1, C1_0, C1_1, U_0, U_1);
    AND_async  u4( S_0, S_1, T_0, T_1, W_0, W_1);
    AND_async u5( U_0, U_1, W_0, W_1, Y_1, Y_0);

endmodule

module OAI222XL_async (A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, B1_0, B1_1, C0_0, C0_1, C1_0, C1_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1_0;
    input   A1_1;
    input   B0_0;
    input   B0_1;
    input   B1_0;
    input   B1_1;
    input   C0_0;
    input   C0_1;
    input   C1_0;
    input   C1_1;
    output  Y_0;
    output  Y_1;
    wire    onset;
    wire    offset; 
    wire    c_0, c_1, c_2, c_3, c_4;
    wire    on0, on1, on2, off0, off1, off2, off3, off4, off5, off6, off7;
    wire    complete;

    OR_async   u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1);
    OR_async   u2( B0_0, B0_1, B1_0, B1_1, T_0, T_1);
    OR_async   u3( C0_0, C0_1, C1_0, C1_1, U_0, U_1);
    AND_async  u4( S_0, S_1, T_0, T_1, W_0, W_1);
    AND_async u5( U_0, U_1, W_0, W_1, Y_1, Y_0);

endmodule

module OAI22X1_async (A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, B1_0, B1_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1_0;
    input   A1_1;
    input   B0_0;
    input   B0_1;
    input   B1_0;
    input   B1_1;
    output  Y_0;
    output  Y_1;

    OR_async   u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1 );
    OR_async   u2( B0_0, B0_1, B1_0, B1_1, T_0, T_1 );
    AND_async u3( S_0, S_1, T_0, T_1, Y_1, Y_0 );


endmodule

module OAI22XL_async (A0_0, A0_1, A1_0, A1_1, B0_0, B0_1, B1_0, B1_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1_0;
    input   A1_1;
    input   B0_0;
    input   B0_1;
    input   B1_0;
    input   B1_1;
    output  Y_0;
    output  Y_1;

    OR_async   u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1 );
    OR_async   u2( B0_0, B0_1, B1_0, B1_1, T_0, T_1 );
    AND_async u3( S_0, S_1, T_0, T_1, Y_1, Y_0 );


endmodule

module OAI2B11X1_async (A0_0, A0_1, A1N_0, A1N_1, B0_0, B0_1, C0_0, C0_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1N_0;
    input   A1N_1;
    input   B0_0;
    input   B0_1;
    input   C0_0;
    input   C0_1;
    output  Y_0;
    output  Y_1;

    ORB_async  u1( A1N_0, A1N_1, A0_0, A0_1, S_0, S_1);
    AND_async  u2( B0_0,  B0_1,  C0_0, C0_1, T_0, T_1);
    AND_async u3( S_0,  S_1,  T_0, T_1, Y_1, Y_0);


endmodule

module OAI2BB1X1_async (A0N_0, A0N_1, A1N_0, A1N_1, B0_0, B0_1, Y_0, Y_1);
    input   A0N_0;
    input   A0N_1;
    input   A1N_0;
    input   A1N_1;
    input   B0_0;
    input   B0_1;
    output  Y_0;
    output  Y_1;

    ORBB_async u1( A0N_0, A0N_1, A1N_0, A1N_1, S_0, S_1 );
    AND_async u2( S_0, S_1, B0_0, B0_1, Y_1, Y_0 );


endmodule

module OAI2B2X1_async (A0_0, A0_1, A1N_0, A1N_1, B0_0, B0_1, B1_0, B1_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1N_0;
    input   A1N_1;
    input   B0_0;
    input   B0_1;
    input   B1_0;
    input   B1_1;
    output  Y_0;
    output  Y_1;

    ORB_async  u1( A1N_0, A1N_1, A0_0, A0_1, S_0, S_1);
    OR_async   u2( B0_0,  B0_1,  B1_0,  B1_1,  T_0, T_1);
    AND_async u3( S_0,  S_1,  T_0,  T_1,  Y_1, Y_0);

endmodule

module OAI2B2XL_async (A0_0, A0_1, A1N_0, A1N_1, B0_0, B0_1, B1_0, B1_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1N_0;
    input   A1N_1;
    input   B0_0;
    input   B0_1;
    input   B1_0;
    input   B1_1;
    output  Y_0;
    output  Y_1;

    ORB_async  u1( A1N_0, A1N_1, A0_0, A0_1, S_0, S_1);
    OR_async   u2( B0_0,  B0_1,  B1_0,  B1_1,  T_0, T_1);
    AND_async u3( S_0,  S_1,  T_0,  T_1,  Y_1, Y_0);

endmodule

module OAI2BB2X1_async (A0N_0, A0N_1, A1N_0, A1N_1, B0_0, B0_1, B1_0, B1_1, Y_0, Y_1);
    input   A0N_0;
    input   A0N_1;
    input   A1N_0;
    input   A1N_1;
    input   B0_0;
    input   B0_1;
    input   B1_0;
    input   B1_1;
    output  Y_0;
    output  Y_1;

    ORBB_async u1( A0N_0, A0N_1, A1N_0, A1N_1, S_0, S_1);
    OR_async   u2( B0_0,  B0_1,  B1_0,  B1_1,  T_0, T_1);
    AND_async u3( S_0,  S_1,  T_0,  T_1,  Y_1, Y_0);


endmodule

module OAI2BB2XL_async (A0N_0, A0N_1, A1N_0, A1N_1, B0_0, B0_1, B1_0, B1_1, Y_0, Y_1);
    input   A0N_0;
    input   A0N_1;
    input   A1N_0;
    input   A1N_1;
    input   B0_0;
    input   B0_1;
    input   B1_0;
    input   B1_1;
    output  Y_0;
    output  Y_1;

    ORBB_async u1( A0N_0, A0N_1, A1N_0, A1N_1, S_0, S_1);
    OR_async   u2( B0_0,  B0_1,  B1_0,  B1_1,  T_0, T_1);
    AND_async u3( S_0,  S_1,  T_0,  T_1,  Y_1, Y_0);


endmodule

module OAI31X1_async (A0_0, A0_1, A1_0, A1_1, A2_0, A2_1, B0_0, B0_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1_0;
    input   A1_1;
    input   A2_0;
    input   A2_1;
    input   B0_0;
    input   B0_1;
    output  Y_0;
    output  Y_1;

    OR_async   u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1);
    OR_async   u2( A2_0, A2_1, S_0,  S_1,  T_0, T_1);
    AND_async u3( B0_0, B0_1, T_0,  T_1,  Y_1, Y_0);

endmodule

module OAI31XL_async (A0_0, A0_1, A1_0, A1_1, A2_0, A2_1, B0_0, B0_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1_0;
    input   A1_1;
    input   A2_0;
    input   A2_1;
    input   B0_0;
    input   B0_1;
    output  Y_0;
    output  Y_1;

    OR_async   u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1);
    OR_async   u2( A2_0, A2_1, S_0,  S_1,  T_0, T_1);
    AND_async u3( B0_0, B0_1, T_0,  T_1,  Y_1, Y_0);

endmodule

module OAI32X1_async (A0_0, A0_1, A1_0, A1_1, A2_0, A2_1, B0_0, B0_1, B1_0, B1_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1_0;
    input   A1_1;
    input   A2_0;
    input   A2_1;
    input   B0_0;
    input   B0_1;
    input   B1_0;
    input   B1_1;
    output  Y_0;
    output  Y_1;

    OR_async   u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1);
    OR_async   u2( A2_0, A2_1, S_0,  S_1,  T_0, T_1);
    OR_async   u3( B0_0, B0_1, B1_0, B1_1, U_0, U_1);
    AND_async u4( U_0, U_1, T_0,  T_1,  Y_1, Y_0);

endmodule

module OAI32XL_async (A0_0, A0_1, A1_0, A1_1, A2_0, A2_1, B0_0, B0_1, B1_0, B1_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1_0;
    input   A1_1;
    input   A2_0;
    input   A2_1;
    input   B0_0;
    input   B0_1;
    input   B1_0;
    input   B1_1;
    output  Y_0;
    output  Y_1;

    OR_async   u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1);
    OR_async   u2( A2_0, A2_1, S_0,  S_1,  T_0, T_1);
    OR_async   u3( B0_0, B0_1, B1_0, B1_1, U_0, U_1);
    AND_async u4( U_0, U_1, T_0,  T_1,  Y_1, Y_0);

endmodule

module OAI33X1_async (A0_0, A0_1, A1_0, A1_1, A2_0, A2_1, B0_0, B0_1, B1_0, B1_1, B2_0, B2_1, Y_0, Y_1);
    input   A0_0;
    input   A0_1;
    input   A1_0;
    input   A1_1;
    input   A2_0;
    input   A2_1;
    input   B0_0;
    input   B0_1;
    input   B1_0;
    input   B1_1;
    input   B2_0;
    input   B2_1;
    output  Y_0;
    output  Y_1;

    OR_async   u1( A0_0, A0_1, A1_0, A1_1, S_0, S_1);
    OR_async   u2( A2_0, A2_1, S_0,  S_1,  T_0, T_1);
    OR_async   u3( B0_0, B0_1, B1_0, B1_1, U_0, U_1);
    OR_async   u4( B2_0, B2_1, U_0,  U_1,  V_0, V_1);
    AND_async u5( T_0,  T_1,  V_0,  V_1,  Y_1, Y_0);

endmodule

module OR2X1_async (A_0, A_1, B_0, B_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    input   B_0;
    input   B_1;
    output  Y_0;
    output  Y_1;
    wire    onset;
    wire    offset; 
    wire    c_0;
    wire    c_1;
    wire    complete;


    OR_async u1( A_0, A_1, B_0, B_1, Y_0, Y_1);

endmodule

module OR4X1_async (A_0, A_1, B_0, B_1, C_0, C_1, D_0, D_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    input   B_0;
    input   B_1;
    input   C_0;
    input   C_1;
    input   D_0;
    input   D_1;
    output  Y_0;
    output  Y_1;
    
    OR_async  u1( A_0, A_1, B_0, B_1, S_0, S_1 );
    OR_async  u2( C_0, C_1, D_0, D_1, T_0, T_1 );
    OR_async u3( S_0, S_1, T_0, T_1, Y_0, Y_1);

endmodule

module XOR2X1_async (A_0, A_1, B_0, B_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    input   B_0;
    input   B_1;
    output  Y_0;
    output  Y_1;

    XOR_async u1( A_0, A_1, B_0, B_1, Y_0, Y_1);
    
    /*
    OR_async   u1( A_0, A_1, B_0, B_1, S_0, S_1);
    AND_async u2( A_0, A_1, B_0, B_1, T_1, T_0);
    AND_async  u3( S_0, S_1, T_0, T_1, Y_0, Y_1);
    */

    // XOR2X1_async m( .A_0(A_0), .A_1(A_1), .B_0(B_0), .B_1(B_1), .Y_0(Y_0), .Y_1(Y_1) );
    //  A  B  Y  
    //  0  0  0
    //  0  1  1
    //  1  0  1
    //  1  1  0
endmodule

module XOR2XL_async (A_0, A_1, B_0, B_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    input   B_0;
    input   B_1;
    output  Y_0;
    output  Y_1;
    XOR_async u1( A_0, A_1, B_0, B_1, Y_0, Y_1);
    
    /*
    OR_async   u1( A_0, A_1, B_0, B_1, S_0, S_1);
    AND_async u2( A_0, A_1, B_0, B_1, T_1, T_0);
    AND_async  u3( S_0, S_1, T_0, T_1, Y_0, Y_1);
    */
endmodule

module XNOR2X1_async (A_0, A_1, B_0, B_1, Y_0, Y_1);
    input   A_0;
    input   A_1;
    input   B_0;
    input   B_1;
    output  Y_0;
    output  Y_1;

    XOR_async u1( A_0, A_1, B_0, B_1, Y_1, Y_0);

endmodule