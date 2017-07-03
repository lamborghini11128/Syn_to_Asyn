// buffer line
module b (in, clk, out);
    input in, clk;
    output out;
    wire a, b, c, d;
    DFFQX1 \p10_reg[23]  ( .D(b), .CK(clk), .Q(a) );
    DFFQX1 \p10_reg[24]  ( .D(c), .CK(clk), .Q(d) );
    CLKINVX1 U5406 ( .A(in), .B(a), .Y(c) .S(b));
    CLKINVX1 U5407 ( .A(b), .B(d), .Y(out));
endmodule
