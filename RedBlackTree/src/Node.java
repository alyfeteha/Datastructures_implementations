////////////////////////////////////////////////////////////////
public class Node {
    private static final boolean Black=true;
    private static final boolean Red=false;
    private String word;
    public boolean color=Red;
    private Node rightNode;
    private Node leftNode;
    private Node parent;

    public Node(Node parent,String word) {
        this.word=word;
        rightNode=null;
        leftNode=null;
        this.parent=parent;
    }

    public void changeColor(){
        if(this.color==Red){
            this.color=Black;
        }
        else{
            this.color=Red;
        }
    }

    public Node getUncle(){
        Node grandpa = this.parent.parent;
        Node uncle =null;
        if(this.parent ==grandpa.leftNode){
            uncle=grandpa.rightNode;
        }
        else if(this.parent ==grandpa.rightNode){
            uncle=grandpa.leftNode;
        }
        return uncle;
    }

    public String getWord() {
        return word;
    }

    public void setWord(String word) {
        this.word = word;
    }

    public boolean isColor() {
        return color;
    }

    public void setColor(boolean color) {
        this.color = color;
    }

    public Node getRightNode() {
        return rightNode;
    }

    public void setRightNode(Node rightNode) {
        this.rightNode = rightNode;
    }

    public Node getLeftNode() {
        return leftNode;
    }

    public void setLeftNode(Node leftNode) {
        this.leftNode = leftNode;
    }

    public Node getParent() {
        return parent;
    }

    public void setParent(Node parent) {
        this.parent = parent;
    }

}