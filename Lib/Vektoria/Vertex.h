#pragma once
#include "../VektoriaMath/HVector.h"
#include "../VektoriaMath/HMat.h"

//--------------------------------------------------------------------------------------------
// CVertex: Klasse für Raumpunkte mit Zusatzinformationen (Normale, Binormale, Tangente, etc.)
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschränkt)
//--------------------------------------------------------------------------------------------

namespace Vektoria
{

	class CVertexs;
	class CFaces;
	class CFace;

class CVertex
{
public:
	///<summary> Konstruktor für Position (0,0,0) und uv-Koordinaten (0,0)).</summary>
	CVertex();

	///<summary> Konstruktor bei der die Bitangente automatisch aus Normale und Tangente berechnet wird.</summary>
	///<param name="vPos">Position des Vertex (W-Faktor muss 1 sein!)</param>
	///<param name="vNormal">Oberflächennormale des Vertex (W-Faktor muss 0 sein!)</param>
	///<param name="vTangent">Oberflächentangente des Vertex (W-Faktor muss 0 sein!), wichtig bei Height- oder Bump-Mapping</param>
	///<param name="fU">U-Komponente der UV-Texturparameter</param>
	///<param name="fV">V-Komponente der UV-Texturparameter</param>
	CVertex(CHVector &  vPos, CHVector & vNormal, CHVector & vTangent, float fU, float fV);

	///<summary> Konstruktor bei der die Bitangente dediziert angegeben wird.</summary>
	///<param name="vPos">Position des Vertex (W-Faktor muss 1 sein!)</param>
	///<param name="vNormal">Oberflächennormale des Vertex (W-Faktor muss 0 sein!)</param>
	///<param name="vTangent">Oberflächentangente des Vertex (W-Faktor muss 0 sein!), wichtig bei Height- oder Bump-Mapping</param>
	///<param name="vBitangent">Oberflächenbitangente des Vertex (W-Faktor muss 0 sein!), wichtig bei Height- oder Bump-Mapping</param>
	///<param name="fU">U-Komponente der UV-Texturparameter</param>
	///<param name="fV">V-Komponente der UV-Texturparameter</param>
	CVertex(CHVector &  vPos, CHVector & vNormal, CHVector & vTangent, CHVector & vBitangent, float fU, float fV);

	///<summary> Destruktor.</summary>
	~CVertex();

	///<summary> Kopieroperator.</summary>
	CVertex operator=(CVertex & vertex);

	///<summary> Kopiert Daten des Vertex in den vorliegenenden Vertex.<para></para>
	/// Achtung! Metadaten (Adjazente Faces und gleichartige Vertices) werden nicht mitkopiert. </summary>
	///<param name="vertex">Zu kopierender Vertex</param>
	void Copy(CVertex & vertex);

	///<summary> Kopiert Vertex inklusive Topologiedaten des Vertex in den vorliegenenden Vertex.<para></para>
	/// Metadaten sind: Adjazente Faces und gleichartige Vertices (m_pfaces, m_pverticesSame). </summary>
	///<param name="vertex">Zu kopierender Vertex</param>
	void CopyTopology(CVertex & vertex);

	///<summary> Matrixmultiplikation aller Werte mit der Matrix m => Verschieben, Rotieren, Skalieren etc. möglich.</summary> 
	///<param name="m">Homogene Transformationsmatrix</param>
	CVertex operator*(CHMat & m);

	///<summary> Vergleicht den Vertex mit dem Vertex v, gibt true aus wenn die beiden Vertices identisch sind.</summary>
	///<param name="vertex">Zu vergleichender Vertex</param>
	///<param name="bCheckNormal">Flag, ob Normalen beim Gleichheitscheck mit berücksichtigt werden</param>
	///<param name="bCheckTangent">Flag, ob Tangenten beim Gleichheitscheck mit berücksichtigt werden</param>
	///<param name="bCheckBitangent">Flag, ob Bitangenten beim Gleichheitscheck mit berücksichtigt werden</param>
	///<param name="bCheckUV">Flag, ob UV-Koordinaten beim Gleichheitscheck mit berücksichtigt werden</param>
	bool Equal(CVertex & vertex, bool bCheckNormal, bool bCheckTangent, bool bCheckBitangent, bool bCheckUV);

	///<summary> Vergleicht den Vertex mit dem Vertex v, gibt true aus wenn die beiden Vertices ähnlich sind.</summary>
	///<param name="vertex">Zu vergleichender Vertex</param>
	///<param name="bCheckNormal">Flag, ob Normalen beim Ähnlichkeitscheck mit berücksichtigt werden</param>
	///<param name="bCheckTangent">Flag, ob Tangenten beim Ähnlichkeitscheck mit berücksichtigt werden</param>
	///<param name="bCheckBitangent">Flag, ob Bitangenten beim Ähnlichkeitscheck mit berücksichtigt werden</param>
	///<param name="bCheckUV">Flag, ob UV-Koordinaten beim Ähnlichkeitscheck mit berücksichtigt werden</param>
	///<param name="fPosThresholdRadius">Oberer Grenzwert für den Abstand zweier Vertexpositionen, bei dem die Vertices als "ähnlich" gelten sollen</param>
	///<param name="faThreshold">Oberer Grenzwert für den Winkel im Bogenmaß zwischen zwei Vertexnormalen, - tangenten oder -bitangenten, bei dem die Vertices als "ähnlich" gelten sollen</param>
	///<param name="fUVThresholdRadius">Oberer Grenzwert für den Abstand zweier UV-Koordinaten, bei dem die Vertices als "ähnlich" gelten sollen</param>
	bool Similar(CVertex & vertex, bool bCheckNormal, bool bCheckTangent, bool bCheckBitangent, bool bCheckUV, float fPosThresholdRadius, float faThreshold, float fUVThresholdRadius);

	///<summary> Initialisiert den Vertex, die Bitangente wird automatisch aus Normale und Tangente berechnet.</summary>
	///<param name="vPos">Position des Vertex (W-Faktor muss 1 sein!)</param>
	///<param name="vNormal">Oberflächennormale des Vertex (W-Faktor muss 0 sein!)</param>
	///<param name="vTangent">Oberflächentangente des Vertex (W-Faktor muss 0 sein!), wichtig bei Height- oder Bump-Mapping</param>
	///<param name="fU">U-Komponente der UV-Texturparameter</param>
	///<param name="fV">V-Komponente der UV-Texturparameter</param>
	void Init(CHVector & vPos, CHVector & vNormal, CHVector & vTangent, float fU = 0, float fV = 0);

	///<summary> Initialisiert den Vertex, die Bitangente wird dediziert angegeben.</summary>
	///<param name="vPos">Position des Vertex (W-Faktor muss 1 sein!)</param>
	///<param name="vNormal">Oberflächennormale des Vertex (W-Faktor muss 0 sein!)</param>
	///<param name="vTangent">Oberflächentangente des Vertex (W-Faktor muss 0 sein!), wichtig bei Height- oder Bump-Mapping</param>
	///<param name="vBitangent">Oberflächenbitangente des Vertex (W-Faktor muss 0 sein!), wichtig bei Height- oder Bump-Mapping</param>
	///<param name="fU">U-Komponente der UV-Texturparameter</param>
	///<param name="fV">V-Komponente der UV-Texturparameter</param>
	void Init(CHVector & vPos, CHVector & vNormal, CHVector & vTangent, CHVector & vBitangent, float fU = 0, float fV = 0);

	///<summary> Deinitialisiert den Vertex.</summary>
	void Fini();

	///<summary> Verschmilzt Normalen-, Tangenten- und Bitangenteninformationen der beiden Vertices this und vertex2.</summary>
	///<param name="vertex">Zu verschmelzender Vertex</param>
	void UniteDirections(CVertex & vertex);

	///<summary> Matrixmultiplikation aller Werte mit der Matrix m => Verschieben, Rotieren, Skalieren etc. möglich.</summary>
	///<param name="m">Homogene Transformationsmatrix</param>
	void Transform(CHMat &m);

	///<summary> Matrixmultiplikation aller Werte mit der Matrix m => Verschieben, Rotieren, Skalieren etc. möglich, schneller als Transform, aber bei Skalierungen und Spiegelungen werden Normalenvektoren falsch berechnet.</summary>
	///<param name="m">Homogene Transformationsmatrix</param>
	void TransformScaleless(CHMat &m);

	///<summary> Matrixmultiplikation der Normalen-, der Tangenten- und der Bitangentenvektoren, Position und UV-Koordinaten werden belassen.</summary>
	///<param name="m">Homogene Transformationsmatrix</param>
	void TransformDirections(CHMat &m); 

	///<summary> Versucht, die Tangenten und die Bitangenten für das Bumpmapping aus den gegebenen UV-Koordianten der zwei aufeinanderfolgenden Vertices im Dreeick zu berechnen.<para></para>
	/// Achtung:  Es kann sich nur um eine Näherungslösung handeln! </summary>
	///<param name="vertex1">Nächster Vertex im Dreieckspolygon</param>
	///<param name="vertex2">Übernächster Vertex (= vorheriger Vertex) im Dreieckspolygon</param>
	void EstimateTangentAndBitangent(CVertex & vertex1, CVertex & vertex2);
	
	///<summary> Versucht, die Tangenten und die Bitangenten für das Bumpmapping aus den gegebenen UV-Koordianten der zwei aufeinanderfolgenden Vertices im Dreeick zu berechnen, <para></para>
	/// addiert die berechneten Werte auf die vorhandenen Tangenten und Bitangenten.<para></para>
	/// Achtung:  Es kann sich nur um eine Näherungslösung handeln! </summary>
	///<param name="vertex1">Nächster Vertex im Dreieckspolygon</param>
	///<param name="vertex2">Übernächster Vertex (= vorheriger Vertex) im Dreieckspolygon</param>
	void EstimateTangentAndBitangentOffset(CVertex & vertex1, CVertex & vertex2);

	///<summary> Setzt Tangente und Bitangente auf Null (0,0,0,0).</summary>
	void ClearTangentAndBitangent();

	///<summary> Interpoliert zwischen Vertex A und Vertex B.</summary>
	///<param name="vertexA">Ausgags-Vertex A</param>
	///<param name="vertexA">Ziel-Vertex B</param>
	///<param name="fr">Laufparameter</param>
	void Interpol(CVertex & vertexA, CVertex & vertexB, float fr, bool bInterpolateNormals = true, bool bInterpolateTangentsAndBitangents = true, bool bInterpolateUV = true);

	///<summary> Fügt dem Vertex eine Facette hinzu, die den Vertex als Eckpunkt hat (optional).</summary>
	///<param name="pface">Pointer zu einem adjazenten Face </param>
	void AddFace(CFace * pface);

	///<summary> Hängt vom Vertex eine Facette wieder ab, gibt true aus, falls es geklappt hat.</summary>
	///<param name="pface">Pointer zu einem adjazenten Face </param>
	bool SubFace(CFace * pface);

	///<summary> Fügt dem Vertex einen anderen Vertex hinzu, der dieselbe Position hat (optional).</summary>
	///<param name="pvertexSame">Pointer zu einem Vertex, der dieselbe Position hat </param>
	void AddVertexSame(CVertex * pvertexSame);

	///<summary> Hängt vom Vertex einen anderen Vertex ab, gibt true aus, falls es geklappt hat.</summary>
	///<param name="pvertexSame">Pointer zu einem Vertex, der dieselbe Position hat </param>
	bool SubVertexSame(CVertex * pvertexSame);

	///<summary> Löscht die Liste auf die gleichen Vertices.</summary>
	void SubAllVerticesSame();

	///<summary> Berechnet Vertexnormale aus den drei adjazenten Flächennormalen, so dass Objekt nach dem Shading gerundet erscheint.</summary>
	void Smooth();

	///<summary> Löscht alle Topologiedaten (zusätzliche Informationen zu adjazenten Faces und ähnlichen Vertices)).</summary>
	void ClearTopology();

	///<summary> Gibt den aktuellen Vertexstatus im Logfile aus. </summary>
	void Log();

	///<summary> Gibt true aus, falls die Oberfläche am Vertex mannigfaltig ist. </summary>
	///<param name="pvertexNext">Pointer zum nächchsten nichtmannigfaligen Vertex (rechtshändige Drehrichtung), falls der Vertex mannigfaltig wird ein Nullptr ausgegeben </param>
	bool IsManifold(CVertex * pvertexNext);

	///<summary> Pointer zum nächchsten nichtmannigfaligen Vertex (rechtshändige Drehrichtung), falls der Vertex mannigfaltig wird ein Nullptr ausgegeben. </summary>
	///<param name="pvertexNext">Pointer zum nächchsten nichtmannigfaligen Vertex (rechtshändige Drehrichtung), falls der Vertex mannigfaltig wird ein Nullptr ausgegeben </param>
	CVertex * IsManifold();

	///<summary> Gibt true aus, wenn die vorliegende Vektorposition auf der Geraden zwischen zwei anderen Vertices liegt.</summary> 
	///<param name="vertexA">Vertex A</param>
	///<param name="vertexB">Vertex B</param>
	///<param name="fAccuracyThreshold">Genauigkeitsschwelle, je größer, desto mehr darf der Punkt von der genauen Geraden abweichen.</param>
	bool IsBetween(CVertex & vertexA, CVertex & vertexB, float fAccuracyThreshold = 0.001f);


	///<summary> Gibt das nächste adjazente Face (rechtshändige Drehrichtung) zu pface aus. </summary>
	///<param name="pface">Ausgangsface, zu dem das nächste Face gesucht wird </param>
	CFace * GetFaceNext(CFace * pface);


	// ----------------
	// Membervariablen:
	// ----------------

	///<summary> Position des Vertex (w-Koordinate muss 1.0f sein!).</summary>
	CHVector m_vPos;

	///<summary> Normale des Vertex (w-Koordinate muss 0.0f sein!).</summary>
	CHVector m_vNormal;

	///<summary> Tangente des Vertex (w-Koordinate muss 0.0f sein!).</summary>
	CHVector m_vTangent;

	///<summary> Bitangente des Vertex (w-Koordinate muss 0.0f sein!).</summary>
	CHVector m_vBitangent;

	///<summary> U-Koordinate für das UV-Mapping.</summary>
	float m_fU; 

	///<summary> V-Koordinate für das UV-Mapping.</summary>
	float m_fV;

	///<summary> Markierungsflag, für viele verschiedene Algorithmen sinnvoll. Sollte nach Ausführung des Algorithmus wieder auf Null gesetzt werden.</summary>
	bool m_bMarked;

	///<summary> Optionale Liste von anderen Vertices mit gleicher Position.</summary>
	CVertexs * m_pverticesSame;

	///<summary> Optionale Liste der Faces, die an den Vertex angrenzen.</summary>
	CFaces * m_pfaces;


};

}