`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/15/2026 03:13:27 PM
// Design Name: 
// Module Name: CS25B052_session6_p1
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



// F = (A& B & C & D) | (~B & C & D & E) | ( ~A & ~B) | (B & C & ~E)

module CS25B052_session6_p1(
    input A , input B , input C , input D ,input E , output F 
    );
    wire nota ,notb , note ;
    wire gate1 , gate2 , gate3 , gate4 ;
    
    not(nota , A);
    not(notb , B);
    not(note , E); 
    
    and(gate1 , A , B , C , D) ;
    and(gate2 ,notb, C, D ,E);
    and(gate3 , nota ,notb);
    and(gate4 , B , C , note);
    
    or(F , gate1 ,gate2 , gate3 , gate4);
    
endmodule
