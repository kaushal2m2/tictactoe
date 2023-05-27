//
//  OptionsViewController.swift
//  tictactoe
//
//  Created by Kaushal Marimuthu on 5/26/23.
//

import UIKit

class OptionsViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }
    
    @IBAction func tapAI(){
        guard let game = storyboard?.instantiateViewController(identifier: "game_vc") as? ViewController else{
            return
        }
        game.setaiq(true)
        present(game, animated: true)
    }
    
    @IBAction func tap2p(){
        guard let game = storyboard?.instantiateViewController(identifier: "game_vc") as? ViewController else{
            return
        }
        game.setaiq(false)
        present(game, animated: true)
    }

}
