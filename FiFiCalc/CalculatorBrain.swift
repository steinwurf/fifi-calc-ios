//
//  CalculatorBrain.swift
//  Calculator
//
//  Copyright © 2016 Steinwurf ApS. All rights reserved.
//

import Foundation

class CalculatorBrain
{
    private var fifiC:fifi_calc_t;
    init() {
         fifiC = new_calc()
    }
    
    deinit {
        delete_calc(fifiC)
    }
    
    private var accumulator: UInt32 = 0
    
    func setOperand(operand: UInt32){
            accumulator = operand
    }
    
    func setField(field:String) {
        switch field {
        case "GF(2)": set_field(fifiC, "binary2")
        case "GF(2⁴)": set_field(fifiC, "binary4")
        case "GF(2⁸)": set_field(fifiC, "binary8")
        case "GF(2¹⁶)": set_field(fifiC, "binary16")
        case "GF(2³²-5)": set_field(fifiC, "prime2325")
        default:
            print("unsupported field: \(field)")
            set_field(fifiC, "binary2")
        }
        
        accumulator = 0
        pending = nil
    }
    
    func maxValue() -> UInt32 {
        return max_value(fifiC)
    }
    
    private let operations:Dictionary<String, Operation> = [
        "±": Operation.UnaryOperation,
        "+": Operation.BinaryOperation,
        "˗": Operation.BinaryOperation,
        "×": Operation.BinaryOperation,
        "÷": Operation.BinaryOperation,
        "=": Operation.Equals
    ]
    
    private enum Operation {
        case UnaryOperation
        case BinaryOperation
        case Equals
    }
    
    func performOperation(symbol: String) {
        if let operation = operations[symbol] {
            switch operation {
            case .UnaryOperation:
                if symbol == "~" {
                    accumulator = invert(fifiC, accumulator)
                }
            case .BinaryOperation:
                executePendingBinaryOperation()
                var function:((UInt32, UInt32) -> (UInt32))?
                var isDivision = false
                if symbol == "+" {
                    function = {add(self.fifiC, $0, $1)}
                }
                else if symbol == "˗" {
                    function = {subtract(self.fifiC, $0, $1)}
                }
                else if symbol == "×" {
                    function = {multiply(self.fifiC, $0, $1)}
                }
                else if symbol == "÷" {
                    function = {divide(self.fifiC, $0, $1)}
                    isDivision = true
                }
                pending = PendingOperationInfo(
                    binaryFunction:function!,
                    isDivision:isDivision,
                    firstOperand:accumulator)
            case .Equals:
                executePendingBinaryOperation()
            }
        }
    }
    
    private func executePendingBinaryOperation(){
        if let p = pending {
            if !(p.isDivision && accumulator == 0) {
                accumulator = p.binaryFunction(p.firstOperand, accumulator)
            }
            else {
                if brainFart != nil {
                    brainFart!()
                }
            }
            pending = nil
        }
    }
    
    private var pending: PendingOperationInfo?
    
    private struct PendingOperationInfo{
        var binaryFunction: (UInt32, UInt32) -> UInt32
        var isDivision: Bool
        var firstOperand: UInt32
    }
    
    var result: UInt32 {
        get {
            return accumulator
        }
    }
    
    func setBrainFartCallback(newBrainFart:(() -> Void)?) {
        brainFart = newBrainFart
    }
    
    private var brainFart:(() -> Void)?
    
}
