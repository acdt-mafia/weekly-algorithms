use std::{io::{self, Read}};

// 시간초과
// GPT는 Euler Tour + Fenwick Tree / Segment Tree 쓰라고 하는데 여기까진 안 함

fn main() {
    // read input
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut lines = input.lines();
    let line = lines.next().unwrap();
    let parts: Vec<usize> = line.split_whitespace().map(|s| s.parse::<usize>().unwrap()).collect();
    let n_nodes: usize = parts[0];
    let n_init_chingchan = parts[1];


    // Main Script

    let line = lines.next().unwrap();
    let parent: Vec<i32> = line.split_whitespace().map(|s| s.parse::<i32>().unwrap()).collect();

    let mut children: Vec<Vec<usize>> = vec![vec![]; n_nodes + 1];

    // 트리 셋업
    for node in 1..=n_nodes {
        let p = parent[node-1];
        if p != -1 { // 사장은 뭔가 정보를 입력할 게 없음
            children[p as usize].push(node);
        }
    }

    // 칭찬 값 부여
    let mut value: Vec<usize> = vec![0usize; n_nodes + 1];

    fn add_chingchan(node: usize, add: usize, children: &Vec<Vec<usize>>, value: &mut Vec<usize>) {
        value[node] += add;
        for &child in &children[node] {
            add_chingchan(child, add, children, value);
        }
    }

    for _ in 0..n_init_chingchan {
        let line: &str = lines.next().unwrap();
        let parts: Vec<usize> = line.split_whitespace().map(|s| s.parse::<usize>().unwrap()).collect();
        let employee_received_chingchan: usize = parts[0];
        let amount_chingchan: usize = parts[1];
        add_chingchan(employee_received_chingchan, amount_chingchan, &children, &mut value);
    }
    
    // index = 노드 번호가 되게 하려고 노드 개수보다 한개 더 많은 element를 가지고 있으니 첫 번째 값은 제거
    println!("{}", value[1..].iter().map(|x| x.to_string()).collect::<Vec<_>>().join(" "));
}