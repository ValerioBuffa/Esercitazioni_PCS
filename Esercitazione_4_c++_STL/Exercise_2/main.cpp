#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include "map"

using namespace std;
using namespace Eigen;

struct PolygonalMesh
{
    unsigned int NumberCell0D;
    std::vector<unsigned int> Cell0DId;
    std::vector<Vector2d> Cell0DCoordinates;
    std::map<unsigned int, list<unsigned int>> Cell0DMarkers;

    unsigned int NumberCell1D;
    std::vector<unsigned int> Cell1DId;
    std::vector<Vector2i> Cell1DVertices;
    std::map<unsigned int, list<unsigned int>> Cell1DMarkers;

    unsigned int NumberCell2D;
    std::vector<unsigned int> Cell2DId;
    std::vector<unsigned int> Cell2DMarker;
    std::vector<VectorXi> Cell2DVertices;
    std::vector<VectorXi> Cell2DEdges;
};

///\brief Import the Polygonal mesh and test if the mesh is correct
///\param mesh: a PolygonalMesh struct
///\return the result of the reading, true if is success, false otherwise
bool ImportMesh(PolygonalMesh& mesh);

///\brief Import the Cell0D properties from Cell0Ds.csv file
///\param mesh: a PolygonalMesh struct
///\return the result of the reading, true if is success, false otherwise
bool ImportCell0Ds(PolygonalMesh& mesh);

///\brief Import the Cell1D properties from Cell1Ds.csv file
///\param mesh: a PolygonalMesh struct
///\return the result of the reading, true if is success, false otherwise
bool ImportCell1Ds(PolygonalMesh& mesh);

///\brief Import the Cell2D properties from Cell2Ds.csv file
///\param mesh: a PolygonalMesh struct
///\return the result of the reading, true if is success, false otherwise
bool ImportCell2Ds(PolygonalMesh& mesh);

// ***************************************************************************
int main()
{
    PolygonalMesh mesh;

    if(!ImportMesh(mesh))
        return 1;

    return 0;
}
// ***************************************************************************
bool ImportMesh(PolygonalMesh& mesh)
{
    if(!ImportCell0Ds(mesh))
        return false;

    else
    {
        cout << "Cell0D marker:" << endl;

        for(auto it = mesh.Cell0DMarkers.begin(); it != mesh.Cell0DMarkers.end(); it++)
        {
            cout << "key:\t" << it->first << "\t values:";

            for(const unsigned int id : it->second)
                cout << "\t" << id;

            cout << endl;
        }
    }

    if(!ImportCell1Ds(mesh))
        return false;

    else
    {
        cout << "Cell1D marker:" << endl;

        for(auto it = mesh.Cell1DMarkers.begin(); it != mesh.Cell1DMarkers.end(); it++)
        {
            cout << "key:\t" << it->first << "\t values:";

            for(const unsigned int id : it->second)
                cout << "\t" << id;

            cout << endl;
        }
    }

    if(!ImportCell2Ds(mesh))
        return false;

    else
    {
        for(unsigned int c = 0; c < mesh.NumberCell2D; c++)
        {
            VectorXi edges = mesh.Cell2DEdges[c];

            for(unsigned int e = 0; e < edges.rows(); e++)
            {
                const unsigned int origin = mesh.Cell1DVertices[edges[e]][0];
                const unsigned int end = mesh.Cell1DVertices[edges[e]][1];

                auto findOrigin = find(mesh.Cell2DVertices[c].begin(), mesh.Cell2DVertices[c].end(), origin);

                if(findOrigin == mesh.Cell2DVertices[c].end()){
                    cerr << "Wrong mesh" << endl;
                    return 2;
                }

                auto findEnd = find(mesh.Cell2DVertices[c].begin(), mesh.Cell2DVertices[c].end(), end);

                if(findEnd == mesh.Cell2DVertices[c].end()){
                    cerr << "Wrong mesh" << endl;
                    return 3;
                }

                cout << "c: " << c << ", origin: " << *findOrigin << ", end: " << *findEnd << endl;
            }
        }
    }

    return true;
}
// ***************************************************************************
bool ImportCell0Ds(PolygonalMesh& mesh)
{
    ifstream file("./Cell0Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;

    while(getline(file, line))
        listLines.push_back(line);

    file.close();

    listLines.pop_front();

    mesh.NumberCell0D = listLines.size();

    if(mesh.NumberCell0D == 0){
        cerr << "There is no cell 0D" << endl;
        return false;
    }

    mesh.Cell0DId.reserve(mesh.NumberCell0D);
    mesh.Cell0DCoordinates.reserve(mesh.NumberCell0D);

    for(const string& line : listLines)
    {
        unsigned int id, marker;
        istringstream converter(line);
        string str;
        Vector2d coord;

        getline(converter, str, ';');
        id = stoi(str);

        getline(converter, str, ';');
        marker = stoi(str);

        getline(converter, str, ';');
        coord(0) = stoi(str);

        getline(converter, str, ';');
        coord(1) = stoi(str);

        mesh.Cell0DId.push_back(id);
        mesh.Cell0DCoordinates.push_back(coord);

        if(marker != 0)
        {
            if(mesh.Cell0DMarkers.find(marker) == mesh.Cell0DMarkers.end())
                mesh.Cell0DMarkers.insert({marker, {id}});

            else
                mesh.Cell0DMarkers[marker].push_back(id);
        }
    }

    file.close();

    return true;
}
// ***************************************************************************
bool ImportCell1Ds(PolygonalMesh& mesh)
{
    ifstream file("./Cell1Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;

    while(getline(file, line))
        listLines.push_back(line);

    listLines.pop_front();

    mesh.NumberCell1D = listLines.size();

    if(mesh.NumberCell1D == 0){
        cerr << "There is no cell 1D" << endl;
        return false;
    }

    mesh.Cell1DId.reserve(mesh.NumberCell1D);
    mesh.Cell1DVertices.reserve(mesh.NumberCell1D);

    for(const string& line : listLines)
    {
        unsigned int id, marker;
        istringstream converter(line);
        string str;
        Vector2i vertices;

        getline(converter, str, ';');
        id = stoi(str);

        getline(converter, str, ';');
        marker = stoi(str);

        getline(converter, str, ';');
        vertices(0) = stoi(str);

        getline(converter, str, ';');
        vertices(1) = stoi(str);

        mesh.Cell1DId.push_back(id);
        mesh.Cell1DVertices.push_back(vertices);

        if(marker != 0)
        {
            if(mesh.Cell1DMarkers.find(marker) == mesh.Cell1DMarkers.end())
                mesh.Cell1DMarkers.insert({marker, {id}});

            else
                mesh.Cell1DMarkers[marker].push_back(id);
        }
    }

    file.close();

    return true;
}
// ***************************************************************************
bool ImportCell2Ds(PolygonalMesh& mesh)
{
    ifstream file("./Cell2Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;

    while(getline(file, line))
        listLines.push_back(line);

    listLines.pop_front();

    mesh.NumberCell2D = listLines.size();

    if(mesh.NumberCell2D == 0){
        cerr << "There is no cell 1D" << endl;
        return false;
    }

    mesh.Cell2DId.reserve(mesh.NumberCell2D);
    mesh.Cell2DMarker.reserve(mesh.NumberCell2D);
    mesh.Cell2DVertices.reserve(mesh.NumberCell2D);
    mesh.Cell2DEdges.reserve(mesh.NumberCell2D);

    for(const string& line : listLines)
    {
        unsigned int id, marker, numVertices, numEdges;
        istringstream converter(line);
        string str;

        getline(converter, str, ';');
        id = stoi(str);

        getline(converter, str, ';');
        marker = stoi(str);

        getline(converter, str, ';');
        numVertices = stoi(str);

        VectorXi vertices(numVertices);

        for(unsigned int i = 0; i < numVertices; i++){
            getline(converter, str, ';');
            vertices(i) = stoi(str);
        }

        getline(converter, str, ';');
        numEdges = stoi(str);

        VectorXi edges(numEdges);

        for(unsigned int i = 0; i < numEdges; i++){
            getline(converter, str, ';');
            edges(i) = stoi(str);
        }

        mesh.Cell2DId.push_back(id);
        mesh.Cell2DMarker.push_back(marker);
        mesh.Cell2DVertices.push_back(vertices);
        mesh.Cell2DEdges.push_back(edges);
    }

    file.close();

    return true;
}
