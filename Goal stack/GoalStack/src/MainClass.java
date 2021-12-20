import java.util.LinkedList;

class Node
{
    String name;
    String on;
    boolean clear;
    Node()
    {
        name="";
        on="";
        clear = false;
    }

    Node(String name, String on, boolean clear)
    {
        this.name = name;
        this.on = on;
        this.clear = clear;
    }

}

class Stack
{
    LinkedList<Node> nodes;
    Stack(int is_start)
    {
        if(is_start==1)
        {
            nodes = new LinkedList<Node>();
            nodes.add(new Node("B", "A", true));
            nodes.add(new Node("A", "table", false));
            nodes.add(new Node("C", "table", true));
            nodes.add(new Node("D", "table", true));
        }
        else
        {
            nodes = new LinkedList<Node>();
            nodes.add(new Node("C","A", true));
            nodes.add(new Node("A","table", false));
            nodes.add(new Node("B","D", true));
            nodes.add(new Node("D","table", false));
        }
    }

    public String toString()
    {
        String output = "";
        for(int i=0; i<nodes.size(); i++)
        {
            output = output + nodes.get(i).name + " on " + nodes.get(i).on + " | clear=" + nodes.get(i).clear+"\n";
        }
        return output;
    }

}

public class MainClass
{
    static Stack start;
    static Stack goal;
    public static void main(String args[])
    {
        start = new Stack(1);
        goal = new Stack(0);
        show(start, goal);
    }

    static void show(Stack start, Stack goal)
    {
        System.out.println("Start:\n"+start);
        System.out.println("Goal:\n"+goal);
        for(int i=0; i<goal.nodes.size(); i++)
        {
            process(goal.nodes.get(i));
        }
        System.out.println("Final State:\n"+start);

    }

    static void process(Node node)
    {
        for(int i=0; i<start.nodes.size(); i++)
        {
            if(start.nodes.get(i).name == node.name && start.nodes.get(i).on == node.on)
            {
                return;
            }
        }
        if(!node.on.equals("table"))
        {
            clear(node.on);
        }
        clear(node.name);
        put(node.name, node.on);
    }

    static void put(String name, String on)
    {
        for(int i=0; i<start.nodes.size(); i++)
        {
            if(start.nodes.get(i).name.equals(name))
            {
                start.nodes.get(i).on = on;
            }
        }

        for(int i=0; i<start.nodes.size(); i++)
        {
            if(start.nodes.get(i).name.equals(on))
            {
                start.nodes.get(i).clear= false;
            }
        }
        System.out.println("Put " +name+ " on "+ on);
    }

    static void clear(String element)
    {
        Node temp=null;
        for(int i=0; i<start.nodes.size(); i++)
        {
            if(start.nodes.get(i).name == element)
                temp = start.nodes.get(i);
        }
        if(!temp.clear)
        {
            System.out.println("Clear "+element);
            for(int i=0; i<start.nodes.size(); i++)
            {
                if(start.nodes.get(i).on == temp.name)
                {
                    clear(start.nodes.get(i).name);
                    put(start.nodes.get(i).name, "table");
                }
            }
            temp.clear = true;

        }
    }
}