//
//  ViewController.swift
//  tictactoe
//
//  Created by Kaushal Marimuthu on 5/3/23.
//

import UIKit
import Foundation

class ViewController: UIViewController {
    
    enum Turn {
        case X
        case O
    }

    
    @IBOutlet weak var turnLabel: UILabel!
    
    @IBOutlet var sqr: [UIButton]!
    
    var firstTurn = Turn.X
    var currentTurn = Turn.X
    var board = [UIButton]()
    
    var xs = 0
    var os = 0
    var X = "X"
    var O = "O"
    
    var aiq = false
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        initBoard()
    }
    
    func setaiq(_ a: Bool){
        aiq = a
    }
    
    func initBoard(){
        for sq in sqr{
            board.append(sq)
        }
    }

    @IBAction func boardTapAction(_ sender: UIButton) {
        addToBoard(sender)
        if(!check() && aiq){
            AIMove()
        }
    }
    
    func check() -> Bool{
        if(checkForVictory(X)){
            xs+=1
            resultAlert(title: "X won")
        }
        else if(checkForVictory(O)){
            os+=1
            resultAlert(title: "O won")
        }
        else if(fullBoard()){
            resultAlert(title: "Draw")
        }
        else{
            return false
        }
        return true
    }
    
    func checkForVictory(_ s :String) -> Bool
    {
        // Horizontal Victory
        if thisSymbol(sqr[0], s) && thisSymbol(sqr[1], s) && thisSymbol(sqr[2], s)
        {
            return true
        }
        if thisSymbol(sqr[3], s) && thisSymbol(sqr[4], s) && thisSymbol(sqr[5], s)
        {
            return true
        }
        if thisSymbol(sqr[6], s) && thisSymbol(sqr[7], s) && thisSymbol(sqr[8], s)
        {
            return true
        }
        
        // Vertical Victory
        if thisSymbol(sqr[0], s) && thisSymbol(sqr[3], s) && thisSymbol(sqr[6], s)
        {
            return true
        }
        if thisSymbol(sqr[1], s) && thisSymbol(sqr[4], s) && thisSymbol(sqr[7], s)
        {
            return true
        }
        if thisSymbol(sqr[2], s) && thisSymbol(sqr[5], s) && thisSymbol(sqr[8], s)
        {
            return true
        }
        
        // Diagonal Victory
        if thisSymbol(sqr[0], s) && thisSymbol(sqr[4], s) && thisSymbol(sqr[8], s)
        {
            return true
        }
        if thisSymbol(sqr[2], s) && thisSymbol(sqr[4], s) && thisSymbol(sqr[6], s)
        {
            return true
        }
        
        return false
    }
    
    
    func thisSymbol(_ button: UIButton, _ symbol: String) -> Bool
    {
        return button.title(for: .normal) == symbol
    }
    
    func resultAlert(title: String)  {
        let msg = "X: " + String(xs) + "\nO: " + String(os)
        let ac = UIAlertController(title: title, message: msg, preferredStyle: .actionSheet)
        ac.addAction(UIAlertAction(title: "Reset", style: .default, handler: { (_) in  self.resetBoard()
        }))
        self.present(ac, animated: true)
    }
    
    func resetBoard() {
        for button in board{
            button.setTitle(nil, for: .normal)
            button.isEnabled = true
        }
        if(firstTurn == Turn.X){
            firstTurn = Turn.O
            turnLabel.text = O
            currentTurn = firstTurn
            if(aiq){
                AIMove()
            }
        }
        else if(firstTurn == Turn.O){
            firstTurn = Turn.X
            turnLabel.text = X
            currentTurn = firstTurn
        }
    }
    
    func fullBoard() -> Bool {
        for button in board{
            if(button.title(for: .normal) == nil){
                return false
            }
        }
        return true
    }
    
    func addToBoard(_ sender: UIButton) {
        if(sender.title(for: .normal) == nil){
            if(currentTurn == Turn.X){
                sender.setTitle(X, for: .normal)
                currentTurn = Turn.O
                turnLabel.text = O
            }
            else if(currentTurn == Turn.O){
                sender.setTitle(O, for: .normal)
                currentTurn = Turn.X
                turnLabel.text = X
            }
            sender.isEnabled = false
        }
    }
    
    func getVal(_ btn: UIButton) -> Int32{
        if(btn.title(for: .normal) == X){
            return 1
        }
        if(btn.title(for: .normal) == O){
            return 2
        }
        return 0
    }
    
    func AIMove(){
        if(currentTurn == Turn.X){
            return
        }
        let ai = CppWrapper().getMove(getVal(sqr[0]),
                                    second:getVal(sqr[1]),
                                    third:getVal(sqr[2]),
                                    fourth:getVal(sqr[3]),
                                    fifth:getVal(sqr[4]),
                                    sixth:getVal(sqr[5]),
                                    seventh:getVal(sqr[6]),
                                    eighth:getVal(sqr[7]),
                                    ninth:getVal(sqr[8]));
          addToBoard(sqr[Int(ai)])
          check()
    }
}

