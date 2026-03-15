use std::{io::{self, Read}};

// #[derive(Clone, Copy, Debug)]
// struct LinkedListNode {
//     value: usize,
//     next: usize,
// }

fn main() {
    // INPUT
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut lines = input.lines();
    let line = lines.next().unwrap();

    let mut parts: Vec<usize> = Vec::new();

    for s in line.split_whitespace() {
        let a= s.parse();
        let b:usize  = a.unwrap();
        parts.push(b);
    }


    // Main Script
    let n: usize = parts[0];
    let k: usize = parts[1];
    
    // let mut linkedlist: Vec<LinkedListNode> = Vec::new();
    let mut out: Vec<usize> = Vec::new();

    // GPT 풀이
    let mut v: Vec<usize> = (1..=n).collect();

    let mut idx: usize = 0;
    while v.len() > 0 {
        idx = (idx + k - 1) % v.len();

        out.push(v.remove(idx));
    }

     print!("<");
    for i in 0..out.len() {
        if i == out.len() - 1 {
            print!("{}", out[i]);
        } else {
            print!("{}, ", out[i]);
        }
    }
    println!(">");

    // 연결리스트 같은 거 쓰지 말자   
    // for _ in 0..(n-1) {
    //     if let Some(&last) = linkedlist.last() {
            // let idx_curr: usize = v.iter().position(|&val| val == last.next).unwrap();
            // let idx_next: usize = (idx_curr+k) % v.len();
            // let val_next = v[idx_next];
            // v.remove(idx_curr);
            // println!("value: {}", last.next);
            // println!("next : {}\n", val_next);
            // println!("now, v: {:#?}", v);
            // linkedlist.push(LinkedListNode {value: last.next, next: val_next});
            // println!("now ll: {:#?}", linkedlist);

            // let val_prevnode = linkedlist.iter().position(|node| node.value == last.value).unwrap();
            // let nextnode: LinkedListNode = linkedlist[(idx_prevnode+k)%n];
            // println!("pop next: {:?}", nextnode.value);
            // out.push(nextnode.value); 
    //     }
    // }
}