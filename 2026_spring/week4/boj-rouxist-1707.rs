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
fn is_bipartite_all(graph: &Graph<usize>) -> bool {
    let mut color: HashMap<usize, i8> = HashMap::new();

    for &start in graph.adj.keys() {
        // already visited in another BFS
        if color.contains_key(&start) {
            continue;
        }

        let mut queue: VecDeque<usize> = VecDeque::new();
        color.insert(start, 1);
        queue.push_back(start);

        while let Some(node) = queue.pop_front() {
            let current_color = color[&node];

            if let Some(neighbors) = graph.neighbors(&node) {
                for &n in neighbors {
                    if !color.contains_key(&n) {
                        color.insert(n, -current_color);
                        queue.push_back(n);
                    } else if color[&n] == current_color {
                        return false;
                    }
                }
            }
        }
    }

    true
}

fn main() {
    // read input
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut lines = input.lines();
    
    let n_cases: usize = lines.next().unwrap().parse().unwrap();


    // Main Script
    for _ in 0..n_cases {
        let line = lines.next().unwrap();
        let mut iter: std::str::SplitWhitespace<'_> = line.split_whitespace();
        let _: usize = iter.next().unwrap().parse().unwrap();
        let n_edges: usize = iter.next().unwrap().parse().unwrap();

        let mut graph  = Graph::new();

        for _ in 0..n_edges {
            let line = lines.next().unwrap();
            let mut iter: std::str::SplitWhitespace<'_> = line.split_whitespace();
    
            let dep: usize = iter.next().unwrap().parse().unwrap();
            let dest: usize = iter.next().unwrap().parse().unwrap();
            
            graph.add_edge(dep, dest);
        }

        if is_bipartite_all(&graph) {
            println!("YES");
        } else {
            println!("NO");
        }
    }
}