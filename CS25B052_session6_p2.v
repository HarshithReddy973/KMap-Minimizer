`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/15/2026 03:13:27 PM
// Design Name: 
// Module Name: CS25B052_session6_p2
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

//F = (~A & ~B & ~C) + (A & B & C ) + (~B & ~C & ~D) + (B & C &D )

module CS25B052_session6_p2(
    input A , input B , input C , input D , output F
    );
    
    wire nota ,notb , notc ,notd ;
    wire gate1,gate2, gate3, gate4;
    
    
    not(nota , A);
    not(notb , B);
    not(notc , C);
    not(notd , D);
    
    and(gate1, nota , notb, notc) ;
    and(gate2 , A , B , C);
    and(gate3 , notb , notc , notD);
    and(gate4 , B , C , D);
    
    or(F , gate1 , gate2,  gate3 , gate4);
    
    
endmodule
