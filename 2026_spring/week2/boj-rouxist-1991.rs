use std::collections::HashMap;
use std::io::{self, Read};
use std::str::Chars;

#[derive(Clone, Copy, Debug)]
struct Node {
    left: Option<char>,
    right: Option<char>,
}

fn preorder(tree: &HashMap<char, Node>, root: char) {
    print!("{}", root);

    if let Some(node) = tree.get(&root) {
        if let Some(left) = node.left {
            preorder(tree, left);
        }
        if let Some(right) = node.right {
            preorder(tree, right);
        }
    }
}

fn inorder(tree: &HashMap<char, Node>, root: char) {
    if let Some(node) = tree.get(&root) {
        if let Some(left) = node.left {
            inorder(tree, left);
        }
    }

    print!("{}", root);

    if let Some(node) = tree.get(&root) {
        if let Some(right) = node.right {
            inorder(tree, right);
        }
    }
}

fn postorder(tree: &HashMap<char, Node>, root: char) {
    if let Some(node) = tree.get(&root) {
        if let Some(left) = node.left {
            postorder(tree, left);
        }
        if let Some(right) = node.right {
            postorder(tree, right);
        }
    }

    print!("{}", root);
}

fn main() {
    // read input
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut lines = input.lines();

    let n: usize = lines.next().unwrap().parse().unwrap();

    let mut tree: HashMap<char, Node> = HashMap::new();

    for _ in 0..n {
        // INPUT
        let line: &str = lines.next().unwrap(); // e.g. "A B C"

        let mut parts: Vec<char> = Vec::new();

        for s in line.split_whitespace() {
            // s is &str in 'SplitWhitespace', e.g. "A", "B", "C"
            let mut a: Chars<'_> = s.chars(); // convert &str "A" to (iterator over) char: 'Chars(['A'])'
            let b: Option<char> = a.next(); // extract 'A' from 'Chars(['A'])'. Returns Some('A')
            let c: char = b.unwrap(); // convert Some('A') to 'A'
            parts.push(c);
        }
        
        // The for loop above is exactly equivalent to:
        // let parts: Vec<char> = line.split_whitespace().map(|s| s.chars().next().unwrap()).collect();


        // Main Script
        let parent = parts[0];
        let left = if parts[1] == '.' { None } else { Some(parts[1]) };
        let right = if parts[2] == '.' { None } else { Some(parts[2]) };

        tree.insert(parent, Node { left, right });
    }
    
    let root = 'A';

    preorder(&tree, root);
    println!();

    inorder(&tree, root);
    println!();

    postorder(&tree, root);
    println!();
}