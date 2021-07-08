/*
 * Copyright (c) 2017 Razeware LLC
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * Notwithstanding the foregoing, you may not use, copy, modify, merge, publish, 
 * distribute, sublicense, create a derivative work, and/or sell copies of the 
 * Software in any work that is designed, intended, or marketed for pedagogical or 
 * instructional purposes related to programming, coding, application development, 
 * or information technology.  Permission for such use, copying, modification,
 * merger, publication, distribution, sublicensing, creation of derivative works, 
 * or sale is expressly withheld.
 *    
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

using UnityEngine;
using System.Collections;

public class GlobalStateManager : MonoBehaviour
{
    private int deadPlayers = 0;    // 死亡したプレイヤーの数
    private int deadPlayerNumber = -1;  // 死亡したプレイヤーの番号

    public void PlayerDied (int playerNumber)
    {
        // 死亡したプレイヤーの数を増やす
        deadPlayers++;

        // 1人のプレイヤーが死亡したら
        if (deadPlayers == 1)
        {
            // 死亡したプレイヤーの番号を保持し
            deadPlayerNumber = playerNumber;

            // 0.3f秒後にCheckPlayersDeath関数を呼び出す
            Invoke("CheckPlayersDeath", 0.3f);
        }
    }

    void CheckPlayersDeath()
    {
        // 死亡したプレイヤーが1人だけの場合
        if (deadPlayers == 1)
        {
            // プレイヤー1が死亡した場合
            if (deadPlayerNumber == 1)
            {
                // プレイヤー2が勝利した
                Debug.Log("プレイヤー2の勝利!!");
            }
            // プレイヤー2が死亡した場合
            else
            {
                // プレイヤー1が勝利した
                Debug.Log("プレイヤー1の勝利!!");
            }
        }
        // すべてのプレイヤーが死亡した場合
        else
        {
            // 引き分け
            Debug.Log("引き分け");
        }
    }
}
