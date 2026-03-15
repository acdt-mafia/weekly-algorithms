// GPT가 풀었어요

use std::io::{self, Read};

struct SegTree {
    n: usize,
    tree: Vec<i32>,
}

impl SegTree {
    fn new(size: usize) -> Self {
        let mut n = 1;
        while n < size { n *= 2; }
        Self { n, tree: vec![0; 2*n] }
    }

    fn update(&mut self, mut i: usize, val: i32) {
        i += self.n;
        self.tree[i] = val;

        while i > 1 {
            i /= 2;
            self.tree[i] = self.tree[i*2].max(self.tree[i*2+1]);
        }
    }

    fn query(&self, mut l: usize, mut r: usize) -> i32 {
        if l > r { return 0; }

        l += self.n;
        r += self.n;

        let mut res = 0;

        while l <= r {
            if l % 2 == 1 {
                res = res.max(self.tree[l]);
                l += 1;
            }

            if r % 2 == 0 {
                res = res.max(self.tree[r]);
                r -= 1;
            }

            l /= 2;
            r /= 2;
        }

        res
    }
}

fn dfs(
    u: usize,
    p: usize,
    g: &Vec<Vec<(usize,i32)>>,
    parent: &mut Vec<usize>,
    depth: &mut Vec<usize>,
    heavy: &mut Vec<usize>,
    size: &mut Vec<usize>,
) {
    size[u] = 1;
    parent[u] = p;

    let mut max_size = 0;

    for &(v,_) in &g[u] {
        if v == p { continue; }

        depth[v] = depth[u] + 1;
        dfs(v,u,g,parent,depth,heavy,size);

        size[u] += size[v];

        if size[v] > max_size {
            max_size = size[v];
            heavy[u] = v;
        }
    }
}

fn decompose(
    u: usize,
    h: usize,
    g: &Vec<Vec<(usize,i32)>>,
    parent: &Vec<usize>,
    heavy: &Vec<usize>,
    head: &mut Vec<usize>,
    pos: &mut Vec<usize>,
    cur_pos: &mut usize,
) {
    head[u] = h;
    pos[u] = *cur_pos;
    *cur_pos += 1;

    if heavy[u] != 0 {
        decompose(heavy[u],h,g,parent,heavy,head,pos,cur_pos);
    }

    for &(v,_) in &g[u] {
        if v != parent[u] && v != heavy[u] {
            decompose(v,v,g,parent,heavy,head,pos,cur_pos);
        }
    }
}

fn query_path(
    mut a: usize,
    mut b: usize,
    seg: &SegTree,
    head: &Vec<usize>,
    parent: &Vec<usize>,
    depth: &Vec<usize>,
    pos: &Vec<usize>,
) -> i32 {

    let mut res = 0;

    while head[a] != head[b] {

        if depth[head[a]] < depth[head[b]] {
            std::mem::swap(&mut a,&mut b);
        }

        let h = head[a];
        res = res.max(seg.query(pos[h], pos[a]));

        a = parent[h];
        if a == 0 { break; }
    }

    if depth[a] > depth[b] {
        std::mem::swap(&mut a,&mut b);
    }

    res = res.max(seg.query(pos[a]+1, pos[b]));

    res
}

fn main() {

    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();

    let n: usize = it.next().unwrap().parse().unwrap();

    let mut g = vec![Vec::new(); n+1];

    let mut edge_u = vec![0; n];
    let mut edge_v = vec![0; n];
    let mut edge_w = vec![0; n];

    for i in 1..n {

        let a: usize = it.next().unwrap().parse().unwrap();
        let b: usize = it.next().unwrap().parse().unwrap();
        let c: i32 = it.next().unwrap().parse().unwrap();

        g[a].push((b,c));
        g[b].push((a,c));

        edge_u[i] = a;
        edge_v[i] = b;
        edge_w[i] = c;
    }

    let mut parent = vec![0; n+1];
    let mut depth = vec![0; n+1];
    let mut heavy = vec![0; n+1];
    let mut size = vec![0; n+1];

    dfs(1,0,&g,&mut parent,&mut depth,&mut heavy,&mut size);

    let mut head = vec![0; n+1];
    let mut pos = vec![0; n+1];
    let mut cur_pos = 0;

    decompose(1,1,&g,&parent,&heavy,&mut head,&mut pos,&mut cur_pos);

    let mut seg = SegTree::new(n);

    for i in 1..n {

        let u = edge_u[i];
        let v = edge_v[i];

        let child = if parent[u] == v { u } else { v };

        seg.update(pos[child], edge_w[i]);
    }

    let q: usize = it.next().unwrap().parse().unwrap();

    for _ in 0..q {

        let cmd: i32 = it.next().unwrap().parse().unwrap();

        if cmd == 1 {

            let idx: usize = it.next().unwrap().parse().unwrap();
            let val: i32 = it.next().unwrap().parse().unwrap();

            edge_w[idx] = val;

            let u = edge_u[idx];
            let v = edge_v[idx];
            let child = if parent[u] == v { u } else { v };

            seg.update(pos[child], val);

        } else {

            let u: usize = it.next().unwrap().parse().unwrap();
            let v: usize = it.next().unwrap().parse().unwrap();

            let ans = query_path(u,v,&seg,&head,&parent,&depth,&pos);

            println!("{}", ans);
        }
    }
}