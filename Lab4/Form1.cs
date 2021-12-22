using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Lab4
{
    public partial class Form1 : Form
    {
        CreateGraph createGraph;
        List<Edge> edges;
        List<Vertex> vertices;
        string str = "";
        int select = -1;
        public Form1()
        {
            InitializeComponent();
            createGraph = new CreateGraph(pictureBox1.Width, pictureBox1.Height);
            edges = new List<Edge>();
            vertices = new List<Vertex>();
            pictureBox1.Image = createGraph.GetBitmap();
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                for (int i = 0; i < vertices.Count; i++)
                {
                    if (Math.Sqrt(Math.Pow(e.X - vertices[i].x, 2) + Math.Pow(e.Y - vertices[i].y, 2)) <= createGraph.R * 1.5)
                        return;

                }
                vertices.Add(new Vertex(e.X, e.Y));
                createGraph.DrawVertex(e.X, e.Y, vertices.Count.ToString());
            }
            else
            {
                for (int i = 0; i < vertices.Count; i++)
                {
                    if (Math.Sqrt(Math.Pow(e.X - vertices[i].x, 2) + Math.Pow(e.Y - vertices[i].y, 2)) <= createGraph.R * 1.5)
                    {
                        if (select == -1)
                        {
                            select = i;
                        }
                        else if (select != i)
                        {
                            edges.Add(new Edge(select, i));
                            createGraph.DrawEdge(vertices[select], vertices[i], edges[edges.Count - 1]);
                            select = -1;
                        }
                        else
                        {
                            select = -1;
                        }
                    }
                }
            }
            createGraph.ClearSheet();
            createGraph.DrawGraph(vertices, edges);
            pictureBox1.Image = createGraph.GetBitmap();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            vertices.Clear();
            edges.Clear();
            createGraph.ClearSheet();
            pictureBox1.Image = createGraph.GetBitmap();
            str = "";
            textBox1.Text = "";
        }
        private void DFS(int index, int count, int[,] matrix, List<int> stack, bool[] used)
        {
            str += (index+1).ToString();
            for (int i = 0; i < count; i++)
            {
                if (matrix[index, i] == 1 && !used[i] && !stack.Contains(i))
                {
                    stack.Add(i);
                    str += " ";
                    DFS(i, count, matrix, stack, used);
                }
            }
            used[index] = true;
            stack.Remove(index);
        }
        private void button1_Click(object sender, EventArgs e)
        {
            str = "";
            textBox1.Text = "";
            if (edges.Count < 1) return;
            int[,] matrix = createGraph.CreateMatrix(edges,vertices.Count);
            List<int> stack = new List<int>();
            bool[] used = new bool[vertices.Count];
            stack.Add(0);
            DFS(0, vertices.Count, matrix, stack, used);
            textBox1.Text = str;
        }
    }
}
