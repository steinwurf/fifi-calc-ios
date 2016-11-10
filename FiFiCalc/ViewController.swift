//
//  ViewController.swift
//  Calculator
//
//  Copyright © 2016 Steinwurf ApS. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    

    @IBOutlet weak var button0: UIButton!
    @IBOutlet weak var button1: UIButton!
    @IBOutlet weak var button2: UIButton!
    @IBOutlet weak var button3: UIButton!
    @IBOutlet weak var button4: UIButton!
    @IBOutlet weak var button5: UIButton!
    @IBOutlet weak var button6: UIButton!
    @IBOutlet weak var button7: UIButton!
    @IBOutlet weak var button8: UIButton!
    @IBOutlet weak var button9: UIButton!
    
    private var buttons = [UIButton]()
    
    private var displayColor:UIColor?
    
    override
    func viewDidLoad() {
        super.viewDidLoad()
        displayColor = display.backgroundColor
        display.backgroundColor = UIColor.clear
        display.layer.backgroundColor = displayColor?.cgColor
        
        brain.setBrainFartCallback(newBrainFart: indicateMistake)
        
        buttons.append(button0)
        buttons.append(button1)
        buttons.append(button2)
        buttons.append(button3)
        buttons.append(button4)
        buttons.append(button5)
        buttons.append(button6)
        buttons.append(button7)
        buttons.append(button8)
        buttons.append(button9)
        updateUI()
        
    }
    
    func updateUI() {
        let maxValue = brain.maxValue()
        for (index, button) in buttons.enumerated() {
            if (UInt32(index) > maxValue) {
                button.isHighlighted = true
                button.isUserInteractionEnabled = false
            }
            else {
                button.isHighlighted = false
                button.isUserInteractionEnabled = true
                
            }
        }
    }
    
    func indicateMistake() {
        let colorAnimation = CABasicAnimation(keyPath: "backgroundColor")
        colorAnimation.fromValue = UIColor.red.cgColor
        colorAnimation.toValue = displayColor!.cgColor
        colorAnimation.duration = 1.0
        display.layer.add(colorAnimation, forKey: colorAnimation.keyPath)
    }
 
    
    @IBOutlet weak var display: UILabel!
    
    var isUserInTheMiddleOfTyping = false
    
    @IBAction func touchDigit(_ sender: UIButton) {
        let digit = sender.currentTitle!
        if isUserInTheMiddleOfTyping {
            let textCurrentlyDisplayed = display.text!
            let newText = textCurrentlyDisplayed + digit
            let newValue = UInt32(newText)
            if newValue != nil && newValue! <= brain.maxValue() {
                display.text = newText
            }
            else {
                indicateMistake()
                return
            }
        }
        else
        {
            display.text = digit
        }
        isUserInTheMiddleOfTyping = true
    }
    
    private var displayValue: UInt32 {
        get {
            return UInt32(display.text!)!
        }
        set {
            display.text = String(newValue)
        }
    }
    
    private var brain = CalculatorBrain()
    
    @IBAction func switchField(_ sender: UISegmentedControl) {
        let index = sender.selectedSegmentIndex
        let title = sender.titleForSegment(at: index)!
        brain.setField(field:title)
        displayValue = brain.result
        updateUI()
    }
    
    @IBAction func performOperation(_ sender: UIButton) {
        if isUserInTheMiddleOfTyping {
            brain.setOperand(operand: displayValue)
            isUserInTheMiddleOfTyping = false
        }

        if let mathmaticalSymbol = sender.currentTitle {
            brain.performOperation(symbol: mathmaticalSymbol)
        }
        displayValue = brain.result
        
    }
}
