using System;
using System.Collections.Generic;
using System.Drawing;

namespace Lab5
{
    class Vertex
    {
        public int x, y;

        public Vertex(int x, int y)
        {
            this.x = x;
            this.y = y;
        }
    }

    class Edge
    {
        public int v1, v2;

        public Edge(int v1, int v2)
        {
            this.v1 = v1;
            this.v2 = v2;
        }
    }
    class CreateGraph
    {
        Bitmap bitmap;
        public Pen blackPen;
        Graphics gr;
        Font fo;
        Brush br;
        PointF point;
        public int R = 20;

        public CreateGraph(int width, int height)
        {
            bitmap = new Bitmap(width, height);
            gr = Graphics.FromImage(bitmap);
            ClearSheet();
            blackPen = new Pen(Color.Black);
            blackPen.Width = 2;
            fo = new Font("Arial", 15);
            br = Brushes.Black;
        }

        public Bitmap GetBitmap()
        {
            return bitmap;
        }

        public void ClearSheet()
        {
            gr.Clear(Color.White);
        }

        public void DrawVertex(int x, int y, string alpha)
        {
            gr.FillEllipse(Brushes.White, (x - R), (y - R), 2 * R, 2 * R);
            gr.DrawEllipse(blackPen, (x - R), (y - R), 2 * R, 2 * R);
            point = new PointF(x - 9, y - 9);
            gr.DrawString(alpha, fo, br, point);
        }

        public void DrawEdge(Vertex V1, Vertex V2, Edge E)
        {
            gr.DrawLine(blackPen, V1.x, V1.y, V2.x, V2.y);
            point = new PointF((V1.x + V2.x) / 2, (V1.y + V2.y) / 2);
            DrawVertex(V1.x, V1.y, (E.v1).ToString());
            DrawVertex(V2.x, V2.y, (E.v2).ToString());
        }

        public void DrawGraph(List<Vertex> V, List<Edge> E)
        {
            for (int i = 0; i < E.Count; i++)
            {
                gr.DrawLine(blackPen, V[E[i].v1].x, V[E[i].v1].y, V[E[i].v2].x, V[E[i].v2].y);
                point = new PointF((V[E[i].v1].x + V[E[i].v2].x) / 2, (V[E[i].v1].y + V[E[i].v2].y) / 2);
            }
            for (int i = 0; i < V.Count; i++)
            {
                DrawVertex(V[i].x, V[i].y, (i+1).ToString());
            }
        }
        public int[,] CreateMatrix(List<Edge> edges, int count)
        {
            int[,] matrix = new int[count, count];
            for(int i = 0; i < count; i++)
            {
                for(int j = 0; j < count; j++)
                {
                    matrix[i, j] = 0;
                }
            }
            for(int i = 0; i < edges.Count; i++)
            {
                matrix[edges[i].v1, edges[i].v2] = 1;
                matrix[edges[i].v2, edges[i].v1] = 1;
            }
            return matrix;
        }
        public bool Check(int[,] matrix, int count)
        {
            int tmp = 0;
            for (int i = 0; i < count; i++)
            {
                tmp = 0;
                for (int j = 0; j < count; j++)
                {
                    if (matrix[i, j] == 1) tmp++;
                }
                if (tmp % 2 == 1) return false;
            }
            return true;
        }
    }
}
