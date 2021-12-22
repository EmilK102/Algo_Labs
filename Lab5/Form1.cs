using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Lab5
{
    public partial class Form1 : Form
    {
        CreateGraph createGraph;
        List<Edge> edges;
        List<Vertex> vertices;
        List<int> list;
        int select = -1;
        string str = "";
        public Form1()
        {
            InitializeComponent();
            createGraph = new CreateGraph(pictureBox1.Width, pictureBox1.Height);
            edges = new List<Edge>();
            vertices = new List<Vertex>();
            list = new List<int>();
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
        private void DFS(int index, int count, int[,] matrix, List<int> stack, bool[] used)
        {
            list.Add(index);
            for (int i = 0; i < count; i++)
            {
                if (matrix[index, i] == 1 && !used[i] && !stack.Contains(i))
                {
                    stack.Add(i);
                    DFS(i, count, matrix, stack, used);
                }
            }
            used[index] = true;
            stack.Remove(index);
        }

        private void Eurler_cicle(int index, int count, int[,] matrix, List<int> stack)
        {
            for (int i = 0; i < count; i++)
            {
                if (matrix[index, i] == 1)
                {
                    stack.Add(i);
                    matrix[index, i] = 0;
                    matrix[i, index] = 0;
                    Eurler_cicle(i, count, matrix, stack);
                }
            }
            str += stack[stack.Count-1]+1;
            str += " ";
            stack.RemoveAt(stack.Count-1);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int[,] matrix = createGraph.CreateMatrix(edges,vertices.Count);
            bool[] used = new bool[vertices.Count];
            List<int> stack = new List<int>();
            stack.Add(0);
            DFS(0, vertices.Count, matrix, stack, used);
            if (list.Count != vertices.Count)
            {
                MessageBox.Show("Граф не содержит эйлерова цикла, так как граф несвязный");
                list.Clear();
                return;
            }
            if (!createGraph.Check(matrix, vertices.Count))
            {
                MessageBox.Show("Граф не содержит эйлерова цикла, так как не все вершины имеют четную степень");
                return;
            }
            stack.Add(0);
            Eurler_cicle(0, vertices.Count, matrix, stack);
            list.Clear();
            textBox1.Text = RevString(str);
            createGraph.ClearSheet();
            createGraph.DrawGraph(vertices, edges);
            pictureBox1.Image = createGraph.GetBitmap();
        }

        private string RevString(string a)
        {
            char[] arr = a.ToCharArray();
            Array.Reverse(arr);
            return new string(arr);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            vertices.Clear();
            edges.Clear();
            createGraph.ClearSheet();
            pictureBox1.Image = createGraph.GetBitmap();
            textBox1.Text = "";
            str = "";
            list.Clear();
        }
    }
}
