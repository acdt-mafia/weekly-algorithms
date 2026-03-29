use std::{io::{self, Read}};
use std::cmp::Reverse;
use std::collections::BinaryHeap;

#[derive(Debug)]
pub struct Graph {
    adj: Vec<Vec<(usize, usize)>>, // (neighbor, cost)
}

impl Graph {
    pub fn new(size: usize) -> Self {
        Self {
            adj: vec![Vec::new(); size+1],
        }
    }

    pub fn add_edge(&mut self, a: usize, b: usize, cost: usize) {
        self.adj[a].push((b, cost));
    }

    pub fn add_undirected_edge(&mut self, a: usize, b: usize, cost: usize) {
        self.adj[a].push((b, cost));
        self.adj[b].push((a, cost));
    }

    pub fn neighbors(&self, node: usize) -> &[(usize, usize)] {
        &self.adj[node]
    }

    pub fn remove_edge(&mut self, a: usize, b: usize) {
        self.adj[a].retain(|&(n, _)| n != b);
    }

    pub fn shortest_path(&self, start: usize, goal: usize) -> Option<(usize, Vec<usize>)> {
        let n = self.adj.len();
        let mut dist = vec![usize::MAX; n];
        let mut prev = vec![None; n];

        let mut heap = BinaryHeap::new();

        dist[start] = 0;
        heap.push((Reverse(0), start));

        while let Some((Reverse(cost), node)) = heap.pop() {
            if node == goal {
                break;
            }

            if cost > dist[node] {
                continue;
            }

            for &(next, edge_cost) in &self.adj[node] {
                let new_cost = cost + edge_cost;

                if new_cost < dist[next] {
                    dist[next] = new_cost;
                    prev[next] = Some(node);
                    heap.push((Reverse(new_cost), next));
                }
            }
        }

        if dist[goal] == usize::MAX {
            return None;
        }

        // reconstruct path
        let mut path = Vec::new();
        let mut current = goal;

        while let Some(p) = prev[current] {
            path.push(current);
            current = p;
        }

        path.push(start);
        path.reverse();

        Some((dist[goal], path))
    }
}

fn main() {
    // read input
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut lines = input.lines();

    let n_vertices: usize = lines.next().unwrap().parse().unwrap();
    let n_edges: usize = lines.next().unwrap().parse().unwrap();

    let mut graph: Graph  = Graph::new(n_vertices);

    // Main Script
    for _ in 0..n_edges {
        let line = lines.next().unwrap();
        let mut iter: std::str::SplitWhitespace<'_> = line.split_whitespace();

        let dep: usize = iter.next().unwrap().parse().unwrap();
        let dest: usize = iter.next().unwrap().parse().unwrap();
        let cost: usize = iter.next().unwrap().parse().unwrap();
        
        graph.add_edge(dep, dest, cost);
    }

    
    let line = lines.next().unwrap();
    let mut iter: std::str::SplitWhitespace<'_> = line.split_whitespace();

    let dep: usize = iter.next().unwrap().parse().unwrap();
    let dest: usize = iter.next().unwrap().parse().unwrap();

    let result = graph.shortest_path(dep, dest);

    if let Some((cost, _)) = result {
        println!("{}", cost);
    }
}