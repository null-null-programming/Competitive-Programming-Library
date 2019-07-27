/*
  AVL Tree
  insert(x) : O(log n)
  remove(x) : O(log n)
  find(x)   : O(log n)
*/

template <typename T>
class AVL {
private:
  struct node {
    T key;
    node *left;
    node *right;
    int height;
  };

  node *root;

  void makeEmpty(node *t) {
    if (t == NULL) return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
  }

  node *insert(const T &x, node *t) {
    if (t == NULL) {
      t = new node;
      t->key = x;
      t->height = 0;
      t->left = t->right = NULL;
    } else if (x < t->key) {
      t->left = insert(x, t->left);
      if (getBalance(t) == 2) {
        if (x < t->left->key) {
          t = SRR(t);
        } else {
          t = DRR(t);
        }
      }
    } else if (x > t->key) {
      t->right = insert(x, t->right);
      if (getBalance(t) == -2) {
        if (x > t->right->key) {
          t = SLR(t);
        } else {
          t = DLR(t);
        }
      }
    }

    t->height = max(height(t->left), height(t->right)) + 1;
    return t;
  }

  node *remove(const T &x, node *t) {
    node *tmp;

    //Not Found
    if (t == NULL) {
      return NULL;

      //Searching
    } else if (x < t->key) {
      t->left = remove(x, t->left);
    } else if (x > t->key) {
      t->right = remove(x, t->right);

      //Found
      //2children
    } else if (t->left && t->right) {
      tmp = findMin(t->right);
      t->key = tmp->key;
      t->right = remove(t->key, t->right);

      //1 or 0 child
    } else {
      tmp = t;
      if (t->left == NULL)
        t = t->right;
      else if (t->right == NULL)
        t = t->left;

      delete tmp;
    }

    if (t == NULL) return t;

    t->height = max(height(t->left), height(t->right)) + 1;

    //if unbalanced
    if (getBalance(t) == 2) {
      if (getBalance(t->left) == 1) {
        return SLR(t);
      } else {
        return DLR(t);
      }
    } else if (getBalance(t) == -2) {
      if (getBalance(t->right) == -1) {
        return SRR(t);
      } else {
        return DRR(t);
      }
    }
    return t;
  }

  //Single Right Rotate
  node *SRR(node *&t) {
    node *u = t->left;
    t->left = u->right;
    u->right = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    u->height = max(height(u->left), t->height) + 1;
    return u;
  }
  //Single Left Rotate
  node *SLR(node *&t) {
    node *u = t->right;
    t->right = u->left;
    u->left = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    u->height = max(height(u->right), t->height) + 1;
    return u;
  }
  //Double Right Rotate
  node *DRR(node *&t) {
    t->left = SLR(t->left);
    return SRR(t);
  }
  //Double Left Rotate
  node *DLR(node *&t) {
    t->right = SRR(t->right);
    return SLR(t);
  }

  //find
  node *findMin(node *t) {
    if (t == NULL) {
      return NULL;
    } else if (t->left == NULL) {
      return t;
    } else {
      return findMin(t->left);
    }
  }

  node *findMax(node *t) {
    if (t == NULL) {
      return NULL;
    } else if (t->right == NULL) {
      return t;
    } else {
      return findMax(t->right);
    }
  }

  node *find(const T &x, node *&t) {
    if (t == NULL) {
      return NULL;
    } else if (x < t->key) {
      return find(x, t->left);
    } else if (x > t->key) {
      return find(x, t->right);
    } else {
      return t;
    }
  }

  int height(node *t) {
    return t == NULL ? -1 : t->height;
  }

  int getBalance(node *t) {
    if (t == NULL) return 0;
    return height(t->left) - height(t->right);
  }

  //order
  void preorder(node *t) {
    if (t == NULL) return;
    cout << t->key << " ";
    preorder(t->left);
    preorder(t->right);
  }

  void inorder(node *t) {
    if (t == NULL) return;
    inorder(t->left);
    cout << t->key << " ";
    inorder(t->right);
  }

  void postorder(node *t) {
    if (t == NULL) return;
    postorder(t->left);
    postorder(t->right);
    cout << t->key << " ";
  }

public:
  AVL() { root = NULL; }

  void insert(T x) {
    root = insert(x, root);
  }
  void remove(T x) {
    root = remove(x, root);
  }
  node *find(T x) {
    root = find(x, root);
  }

  T getMax() {
    return findMax(root)->key;
  }
  T getMin() {
    return findMin(root)->key;
  }

  void display() {
    inorder(root);
    cout << endl;
  }
};
