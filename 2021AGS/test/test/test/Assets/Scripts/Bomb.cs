using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bomb : MonoBehaviour
{
    public GameObject expIosionPrefab;  // 爆発エフェクトのプレハブ
    public LayerMask levelMask; // ステージのレイヤー
    private bool exploded = false;  // すでに爆発している場合　true

    // Start is called before the first frame update
    void Start()
    {
        // 3秒後にExplode関数を実行
        Invoke("Explode", 3f);
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    // 爆弾が爆発するときの処理
    private void Explode()
    {
        // 爆発の位置に爆発エフェクトを作成
        Instantiate(expIosionPrefab, transform.position, Quaternion.identity);

        // 爆弾を非表示にする
        GetComponent < MeshRenderer>().enabled = false;

        // 爆発した
        exploded = true;
        // 爆風を広げる
        StartCoroutine(CreateExplosions(Vector3.forward)); // 上に広げる
        StartCoroutine(CreateExplosions(Vector3.right)); // 右に広げる
        StartCoroutine(CreateExplosions(Vector3.back)); // 下に広げる
        StartCoroutine(CreateExplosions(Vector3.left)); // 左に広げる

        transform.Find("Collider").gameObject.SetActive(false);

        // 0.3秒後に非表示のした爆弾を削除
        Destroy(gameObject, 0.3f);
    }

    // 爆風を広げる
    private IEnumerator CreateExplosions(Vector3 direction)
    {
        // 2マス分ループする
        for (int i = 1; i < 3;i++)
        {
            // ブロックとの当たり判定の結果を格納する変数
            RaycastHit hit;

            // 爆風を広げた先に何か存在するか確認
            Physics.Raycast
                (
                transform.position + new Vector3(0, 0.5f, 0),
                direction,
                out hit,
                1,
                levelMask
            );

            // 暴風を広げた先に何も存在しない場合
            if (!hit.collider)
            {
                // 爆風を広げるために、
                // 爆発エフェクトのオブジェクトを作成
                Instantiate
                    (
                    expIosionPrefab,
                    transform.position + (i * direction),
                    expIosionPrefab.transform.rotation
                    );
            }

            // 爆風を広げた先にブロックが存在する場合
            else
            {
                // 爆風はこれ以上広げない
                break;
            }

            // 0.05秒待ってから、次のマスに爆風を広げる
            yield return new WaitForSeconds(0.05f);
        }
    }

    // 他のオブジェクトがこの爆弾に当たったら呼び出される
    public void OnTrigger(Collider other)
    {
        // まだ爆発していない
        // かつ、この爆弾にぶつかったオブジェクトが爆発エフェクトの場合
        if (!exploded && other.CompareTag("Explosion"))
        {
            // 2重に爆発処理が実行されないように
            // すでに爆発処理が実行されている場合は止める
            CancelInvoke("Explode");

            // 爆発する
            Explode();
        }
    }
}
