// 오답

use std::collections::HashMap;
use std::io::{self, Read};

#[derive(Clone, Copy, Debug)]
struct Node {
    left: Option<(usize, u32)>,   // (child, weight)
    right: Option<(usize, u32)>,  // (child, weight)
}

fn main() {
    // read input
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut lines = input.lines();

    let n: usize = lines.next().unwrap().parse().unwrap();

    let mut tree: HashMap<usize, Node> = HashMap::new();

    for _ in 0..(n - 1) {
        let line = lines.next().unwrap();

        let parts: Vec<usize> = line
            .split_whitespace()
            .map(|s| s.parse::<usize>().unwrap())
            .collect();

        let parent = parts[0];
        let child = parts[1];
        let weight = parts[2] as u32;

        let node = tree.entry(parent).or_insert(Node {
            left: None,
            right: None,
        });

        if node.left.is_none() {
            node.left = Some((child, weight));
        } else {
            node.right = Some((child, weight));
        }

        // ensure child node exists
        tree.entry(child).or_insert(Node {
            left: None,
            right: None,
        });
    }

    let root = 1;

    let mut diameter = 0;
    dfs(root, &tree, &mut diameter);

    println!("{}", diameter);
}

fn dfs(node: usize, tree: &HashMap<usize, Node>, diameter: &mut u32) -> u32 {
    let current = tree.get(&node).unwrap();

    let mut left_sum = 0;
    if let Some((child, w)) = current.left {
        left_sum = w + dfs(child, tree, diameter);
    }

    let mut right_sum = 0;
    if let Some((child, w)) = current.right {
        right_sum = w + dfs(child, tree, diameter);
    }

    // update global diameter
    *diameter = (*diameter).max(left_sum + right_sum);

    // return longest downward path
    left_sum.max(right_sum)
}