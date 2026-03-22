use std::{io::{self, Read}};

struct LCA {
    up: Vec<Vec<usize>>,
    depth: Vec<usize>,
    log: usize,
}

impl LCA {
    fn new(n: usize, adj: &Vec<Vec<usize>>, edges: &Vec<(usize, usize)>) -> Self {
        // ---- 1) detect root automatically ----
        let root = {
            use std::collections::HashSet;
            let mut parents = HashSet::new();
            let mut children = HashSet::new();

            for &(p, c) in edges {
                parents.insert(p);
                children.insert(c);
            }

            *parents.difference(&children).next().unwrap()
        };

        let log = (n as f64).log2() as usize + 1;
        let mut up = vec![vec![0; n]; log];
        let mut depth = vec![0; n];

        // ---- 2) DFS using stack (no borrow issues) ----
        let mut stack = vec![(root, root)];

        while let Some((v, p)) = stack.pop() {
            up[0][v] = p;

            for &to in &adj[v] {
                if to != p {
                    depth[to] = depth[v] + 1;
                    stack.push((to, v));
                }
            }
        }

        // ---- 3) Build binary lifting table ----
        for k in 1..log {
            for v in 0..n {
                up[k][v] = up[k - 1][up[k - 1][v]];
            }
        }

        LCA { up, depth, log }
    }

    fn lift(&self, mut v: usize, d: usize) -> usize {
        for i in 0..self.log {
            if d & (1 << i) != 0 {
                v = self.up[i][v];
            }
        }
        v
    }

    fn query(&self, mut a: usize, mut b: usize) -> usize {
        if self.depth[a] < self.depth[b] {
            std::mem::swap(&mut a, &mut b);
        }

        // lift 'a' to same depth
        a = self.lift(a, self.depth[a] - self.depth[b]);

        if a == b {
            return a;
        }

        for i in (0..self.log).rev() {
            if self.up[i][a] != self.up[i][b] {
                a = self.up[i][a];
                b = self.up[i][b];
            }
        }

        self.up[0][a]
    }
}

fn main() {
    // read input
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut lines = input.lines();

    let n_cases: usize = lines.next().unwrap().parse().unwrap();


    // Main Script
    for _ in 0..n_cases {
        let n_nodes: usize = lines.next().unwrap().parse().unwrap();
        let mut adj: Vec<Vec<usize>> = vec![Vec::new(); n_nodes];
        let mut edges: Vec<(usize, usize)> = Vec::new(); // 
        
        
        for _ in 0..n_nodes-1 {
            let line = lines.next().unwrap();
            let parts: Vec<usize> = line.split_whitespace().map(|s| s.parse::<usize>().unwrap()).collect();

            // input은 숫자이지만 adj에는 index로 입력해야 함
            adj[parts[0]-1].push(parts[1]-1);
            adj[parts[1]-1].push(parts[0]-1);
            
            edges.push((parts[0]-1, parts[1]-1));
        }

        let lca: LCA = LCA::new(n_nodes, &adj, &edges);

        // find LCA of two nodes
        let line = lines.next().unwrap();
        let parts: Vec<usize> = line.split_whitespace().map(|s| s.parse::<usize>().unwrap()).collect();
        let ancestor = lca.query(parts[0]-1, parts[1]-1);

        println!("{}", ancestor+1); // 출력은 index가 아닌 노드 번호로
    }

}