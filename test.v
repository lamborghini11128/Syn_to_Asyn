module test1( a, b, c, clk );
    input  [7:0] a;
    input  [7:0] b;
    input        clk;
    output [7:0] c;

    reg    [7:0] p1, next_p1;
    reg    [7:0] p2, next_p2;


    always@(*) begin
        next_p1 = a + b;
    end

    always@(*) begin
        next_p2 = { 4'b0, p1[3:0] } * { 4'b0, p1[7:4] }; 
    end

    assign c = { 4'b0, p2[3:0] } * { 4'b0, p2[7:4] };

    always@( posedge clk )begin 
        p1 = next_p1;
        p2 = next_p2;
    end


endmodule