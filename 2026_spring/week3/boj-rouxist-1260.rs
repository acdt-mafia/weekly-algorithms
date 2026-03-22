use std::{io::{self, Read}};
use std::collections::{HashMap, HashSet, VecDeque};

#[derive(Debug)]
pub struct Graph<I32> {
    adj: HashMap<I32, HashSet<I32>>,
}

impl<I32: Eq + std::hash::Hash + Clone> Graph<I32> {
    pub fn new() -> Self {
        Self {
            adj: HashMap::new(),
        }
    }

    pub fn add_node(&mut self, node: I32) {
        self.adj.entry(node).or_insert(HashSet::new());
    }

    pub fn add_edge(&mut self, a: I32, b: I32) {
        self.add_node(a.clone());
        self.add_node(b.clone());

        self.adj.get_mut(&a).unwrap().insert(b.clone());
        self.adj.get_mut(&b).unwrap().insert(a); // undirected
    }

    pub fn neighbors(&self, node: &I32) -> Option<&HashSet<I32>> {
        self.adj.get(node)
    }

    pub fn remove_edge(&mut self, a: &I32, b: &I32) {
        if let Some(set) = self.adj.get_mut(a) {
            set.remove(b);
        }
        if let Some(set) = self.adj.get_mut(b) {
            set.remove(a);
        }
    }

    pub fn remove_node(&mut self, node: &I32) {
        if let Some(neighbors) = self.adj.remove(node) {
            for n in neighbors {
                if let Some(set) = self.adj.get_mut(&n) {
                    set.remove(node);
                }
            }
        }
    }
}

// GPT가 만듦

fn bfs(graph: &Graph<i32>, start: i32) -> Vec<i32> {
    let mut visited: HashSet<i32> = HashSet::new();
    let mut queue: VecDeque<i32> = VecDeque::new();
    let mut order: Vec<i32> = Vec::new();

    visited.insert(start);
    queue.push_back(start);

    while let Some(node) = queue.pop_front() {
        order.push(node);

        if let Some(neighbors) = graph.neighbors(&node) {
            let mut neighbors: Vec<i32> = neighbors.iter().cloned().collect();
            neighbors.sort();

            for n in neighbors {
                if visited.insert(n) {
                    queue.push_back(n);
                }
            }
        }
    }

    order
}

// GPT가 만듦
fn dfs(graph: &Graph<i32>, start: i32) -> Vec<i32> {
    let mut visited: HashSet<i32> = HashSet::new();
    let mut stack: Vec<i32> = vec![start];
    let mut order: Vec<i32> = Vec::new();

    while let Some(node) = stack.pop() {
        if visited.insert(node) {
            order.push(node);

            if let Some(neighbors) = graph.neighbors(&node) {
                let mut neighbors: Vec<i32> = neighbors.iter().cloned().collect();
                neighbors.sort_by(|a, b| b.cmp(a));

                for n in neighbors {
                    stack.push(n);
                }
            }
        }
    }

    order
}

fn main() {
    // read input
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut lines = input.lines();

    let mut parts: Vec<i32> = Vec::new();

    for n in lines.next().unwrap().split_whitespace() {
        let i:i32 = n.parse().unwrap();
        parts.push(i);
    }

    let n_edges:i32 = parts[1];
    let start_node:i32 = parts[2];


    // Main Script
    let mut graph = Graph::new();

    // Add node, edges
    for _ in 0..n_edges {
        let line = lines.next().unwrap();
        let mut iter = line.split_whitespace();

        let node_a: i32 = iter.next().unwrap().parse().unwrap();
        let node_b: i32 = iter.next().unwrap().parse().unwrap();

        graph.add_edge(node_a,node_b);
    
    }
    
    let res_dfs: Vec<i32> = dfs(&graph, start_node);
    println!("{}", res_dfs.iter().map(|x| x.to_string()).collect::<Vec<_>>().join(" "));

    let res_bfs: Vec<i32> = bfs(&graph, start_node);
    println!("{}", res_bfs.iter().map(|x| x.to_string()).collect::<Vec<_>>().join(" "));
}