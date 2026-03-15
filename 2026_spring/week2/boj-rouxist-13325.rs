// GPT가 풀었어요

use std::io::{self, Read};

fn dfs(node: usize, tree: &Vec<i32>, ans: &mut i32, n: usize) -> i32 {

    let left = node * 2;
    let right = node * 2 + 1;

    if left > n {
        return 0;
    }

    let left_sum = tree[left] + dfs(left, tree, ans, n);
    let right_sum = tree[right] + dfs(right, tree, ans, n);

    *ans += (left_sum - right_sum).abs();

    left_sum.max(right_sum)
}

fn main() {
    // INPUT
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();

    let mut it = input.split_whitespace();

    let k: usize = it.next().unwrap().parse().unwrap();
    let edge_count = (1 << (k+1)) - 2;

    // Main Script
    let mut tree = vec![0; edge_count + 2];

    for i in 2..=edge_count+1 {
        tree[i] = it.next().unwrap().parse().unwrap();
    }

    let mut ans = 0;

    dfs(1, &tree, &mut ans, edge_count+1);

    let total: i32 = tree.iter().sum();

    println!("{}", total + ans);
}