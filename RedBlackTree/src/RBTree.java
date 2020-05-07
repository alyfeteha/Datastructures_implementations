public class RBTree {
    private Node root;
    private int size;
    private int height;
    private int isfound;
    private static final boolean Red=false;
    private static final boolean Black=true;

    public RBTree() {
        this.root = null;
        this.height=-1;
        this.size=0;
        this.isfound=0;
    }

    private Node insertBST(Node root,Node node,Node parent){
        if(root==null){
            node.setParent(parent);
            root=node;
            this.size++;
        }
        else if(node.getWord().compareTo(root.getWord())>0){
            root.setRightNode(insertBST(root.getRightNode(),node,root));
        }
        else if(node.getWord().compareTo(root.getWord())<0){
            root.setLeftNode(insertBST(root.getLeftNode(),node,root));
        }
        return root;
    }



    public void insert(Node node){

        search(root,node.getWord());
        if(this.isfound==1) {
            System.out.println("Error is already in the dictionary!");
            this.isfound=0;
            return;
        }

        this.root=insertBST(this.root,node,null);
        //System.out.println(root.getWord());
        if(size==1){
            root.changeColor();
        }
        checkUncle(node);
        this.height = updateHeight(root);
        System.out.println("Tree Size: "+this.size+"\n"+
                "Tree Height: "+this.height +"\n"+ node.getWord() +"\n");
    }

    private void checkUncle(Node node){
        if(node==this.root || node.getParent().color==Black){
            return;
        }
        Node uncle=node.getUncle();
        if(uncle==null || uncle.color==Black){
            bCase(node);
        }

        else if(uncle.color==Red){
            rCase(node);
        }
    }

    private void rCase(Node node){
        Node grandpa=node.getParent().getParent();
        Node uncle = node.getUncle();
        uncle.changeColor();
        node.getParent().changeColor();
        grandpa.changeColor();
        if(this.root.color==Red){
            this.root.changeColor();
        }
        checkUncle(grandpa);
    }

    private void bCase(Node node){
        Node grandpa = node.getParent().getParent();
        if(grandpa.getLeftNode() == node.getParent() && grandpa.getLeftNode().getLeftNode() == node){  //left left
            node.getParent().changeColor();
            grandpa.changeColor();
            Node x =rotateRight(grandpa);
            if(x.getParent()==null){
                root=x;
            }

        }
        else if(grandpa.getLeftNode() == node.getParent() && grandpa.getLeftNode().getRightNode() == node){  //left right
            Node x = rotateLeft(node.getParent());
            x.changeColor();
            x.getParent().changeColor();
            Node y = rotateRight(x.getParent());
            if(y.getParent()==null){
                root=y;
            }

        }
        else if(grandpa.getRightNode() == node.getParent() && grandpa.getRightNode().getRightNode() == node){  //right right
            node.getParent().changeColor();
            grandpa.changeColor();
            Node x =rotateLeft(grandpa);
            if(x.getParent()==null){
                root=x;
            }

        }
        else if(grandpa.getRightNode() == node.getParent() && grandpa.getRightNode().getLeftNode() == node){  //right left
            Node x = rotateRight(node.getParent());
            x.changeColor();
            x.getParent().changeColor();
            Node y = rotateLeft(x.getParent());
            if(y.getParent()==null){
                root=y;
            }
        }
    }

    private Node rotateRight(Node g){
        Node temp = g.getParent();
        Node p = g.getLeftNode();
        Node T3 = p.getRightNode();
        if(temp!=null && g==temp.getLeftNode()){
            temp.setLeftNode(p);
        }
        else if(temp!=null){
            temp.setRightNode(p);
        }

        p.setRightNode(g);
        g.setParent(p);
        g.setLeftNode(T3);
        if(T3!=null)
            T3.setParent(g);
        p.setParent(temp);

        return p;

    }

    private Node rotateLeft(Node g){
        Node temp = g.getParent();
        Node p = g.getRightNode();
        Node T3 = p.getLeftNode();
        if(temp!=null && g==temp.getLeftNode()){
            temp.setLeftNode(p);
        }
        else if(temp!=null){
            temp.setRightNode(p);
        }

        p.setLeftNode(g);
        g.setParent(p);
        g.setRightNode(T3);
        if(T3!=null)
            T3.setParent(g);
        p.setParent(temp);

        return p;
    }

    private int updateHeight(Node root){
        return root==null ? -1 : 1 + Math.max(updateHeight(root.getLeftNode()),updateHeight(root.getRightNode()));
    }



    public void inOrderTraversal(Node node){
        if (node == null)
            return;
        inOrderTraversal(node.getLeftNode());
        System.out.println(node.getWord());
        inOrderTraversal(node.getRightNode());
    }

    public void search(Node root,String word){
        if(root==null){
            return;
            //return false;
        }
        else if(word.compareTo(root.getWord())==0){
            //System.out.println(root.getWord()+":  found");
            this.isfound=1;
            return;
            //return true;
        }
        else if(word.compareTo(root.getWord())<0){
            // return search(root.getLeftNode(),word);
            search(root.getLeftNode(),word);
        }
        else if(word.compareTo(root.getWord())>0){
            // return search(root.getRightNode(),word);
            search(root.getRightNode(),word);

        }
        //System.out.println("not found");
    }
    public void lookup(Node root,String word){
        if(root==null){
            System.out.println(word + ": not found");
            //return false;
        }
        else if(word.compareTo(root.getWord())==0){
            System.out.println(root.getWord()+":  found");
            //this.isfound=1;

            //return true;
        }
        else if(word.compareTo(root.getWord())<0){
            // return search(root.getLeftNode(),word);
            lookup(root.getLeftNode(),word);
        }
        else {
            // return search(root.getRightNode(),word);
            lookup(root.getRightNode(),word);

        }
        //System.out.println("not found");
    }
    public Node searchNode(Node root, String word)
    {
        // Base Cases: root is null or key is present at root
        if (root==null || root.getWord().compareTo(word)==0)
            return root;

        // val is greater than root's key
        if (root.getWord().compareTo(word)>0)
            return searchNode(root.getLeftNode(), word);

        // val is less than root's key
        return searchNode(root.getRightNode(), word);
    }


    public int getHeight(){
        return height;
    }

    public Node getRoot() {
        return root;
    }


    public int getSize() {
        return size;
    }
}
