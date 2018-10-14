#pragma once
#include "../VektoriaMath/HVector.h"
#include "../VektoriaMath/HMat.h"

//--------------------------------------------------------------------------------------------
// CVertex: Klasse f�r Raumpunkte mit Zusatzinformationen (Normale, Binormale, Tangente, etc.)
//
// Autor: Prof. Dr. Tobias Breiner
// Firma: Vektoria UG (haftungsbeschr�nkt)
//--------------------------------------------------------------------------------------------

namespace Vektoria
{

	class CVertexs;
	class CFaces;
	class CFace;

class CVertex
{
public:
	///<summary> Konstruktor f�r Position (0,0,0) und uv-Koordinaten (0,0)).</summary>
	CVertex();

	///<summary> Konstruktor bei der die Bitangente automatisch aus Normale und Tangente berechnet wird.</summary>
	///<param name="vPos">Position des Vertex (W-Faktor muss 1 sein!)</param>
	///<param name="vNormal">Oberfl�chennormale des Vertex (W-Faktor muss 0 sein!)</param>
	///<param name="vTangent">Oberfl�chentangente des Vertex (W-Faktor muss 0 sein!), wichtig bei Height- oder Bump-Mapping</param>
	///<param name="fU">U-Komponente der UV-Texturparameter</param>
	///<param name="fV">V-Komponente der UV-Texturparameter</param>
	CVertex(CHVector &  vPos, CHVector & vNormal, CHVector & vTangent, float fU, float fV);

	///<summary> Konstruktor bei der die Bitangente dediziert angegeben wird.</summary>
	///<param name="vPos">Position des Vertex (W-Faktor muss 1 sein!)</param>
	///<param name="vNormal">Oberfl�chennormale des Vertex (W-Faktor muss 0 sein!)</param>
	///<param name="vTangent">Oberfl�chentangente des Vertex (W-Faktor muss 0 sein!), wichtig bei Height- oder Bump-Mapping</param>
	///<param name="vBitangent">Oberfl�chenbitangente des Vertex (W-Faktor muss 0 sein!), wichtig bei Height- oder Bump-Mapping</param>
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

	///<summary> Matrixmultiplikation aller Werte mit der Matrix m => Verschieben, Rotieren, Skalieren etc. m�glich.</summary> 
	///<param name="m">Homogene Transformationsmatrix</param>
	CVertex operator*(CHMat & m);

	///<summary> Vergleicht den Vertex mit dem Vertex v, gibt true aus wenn die beiden Vertices identisch sind.</summary>
	///<param name="vertex">Zu vergleichender Vertex</param>
	///<param name="bCheckNormal">Flag, ob Normalen beim Gleichheitscheck mit ber�cksichtigt werden</param>
	///<param name="bCheckTangent">Flag, ob Tangenten beim Gleichheitscheck mit ber�cksichtigt werden</param>
	///<param name="bCheckBitangent">Flag, ob Bitangenten beim Gleichheitscheck mit ber�cksichtigt werden</param>
	///<param name="bCheckUV">Flag, ob UV-Koordinaten beim Gleichheitscheck mit ber�cksichtigt werden</param>
	bool Equal(CVertex & vertex, bool bCheckNormal, bool bCheckTangent, bool bCheckBitangent, bool bCheckUV);

	///<summary> Vergleicht den Vertex mit dem Vertex v, gibt true aus wenn die beiden Vertices �hnlich sind.</summary>
	///<param name="vertex">Zu vergleichender Vertex</param>
	///<param name="bCheckNormal">Flag, ob Normalen beim �hnlichkeitscheck mit ber�cksichtigt werden</param>
	///<param name="bCheckTangent">Flag, ob Tangenten beim �hnlichkeitscheck mit ber�cksichtigt werden</param>
	///<param name="bCheckBitangent">Flag, ob Bitangenten beim �hnlichkeitscheck mit ber�cksichtigt werden</param>
	///<param name="bCheckUV">Flag, ob UV-Koordinaten beim �hnlichkeitscheck mit ber�cksichtigt werden</param>
	///<param name="fPosThresholdRadius">Oberer Grenzwert f�r den Abstand zweier Vertexpositionen, bei dem die Vertices als "�hnlich" gelten sollen</param>
	///<param name="faThreshold">Oberer Grenzwert f�r den Winkel im Bogenma� zwischen zwei Vertexnormalen, - tangenten oder -bitangenten, bei dem die Vertices als "�hnlich" gelten sollen</param>
	///<param name="fUVThresholdRadius">Oberer Grenzwert f�r den Abstand zweier UV-Koordinaten, bei dem die Vertices als "�hnlich" gelten sollen</param>
	bool Similar(CVertex & vertex, bool bCheckNormal, bool bCheckTangent, bool bCheckBitangent, bool bCheckUV, float fPosThresholdRadius, float faThreshold, float fUVThresholdRadius);

	///<summary> Initialisiert den Vertex, die Bitangente wird automatisch aus Normale und Tangente berechnet.</summary>
	///<param name="vPos">Position des Vertex (W-Faktor muss 1 sein!)</param>
	///<param name="vNormal">Oberfl�chennormale des Vertex (W-Faktor muss 0 sein!)</param>
	///<param name="vTangent">Oberfl�chentangente des Vertex (W-Faktor muss 0 sein!), wichtig bei Height- oder Bump-Mapping</param>
	///<param name="fU">U-Komponente der UV-Texturparameter</param>
	///<param name="fV">V-Komponente der UV-Texturparameter</param>
	void Init(CHVector & vPos, CHVector & vNormal, CHVector & vTangent, float fU = 0, float fV = 0);

	///<summary> Initialisiert den Vertex, die Bitangente wird dediziert angegeben.</summary>
	///<param name="vPos">Position des Vertex (W-Faktor muss 1 sein!)</param>
	///<param name="vNormal">Oberfl�chennormale des Vertex (W-Faktor muss 0 sein!)</param>
	///<param name="vTangent">Oberfl�chentangente des Vertex (W-Faktor muss 0 sein!), wichtig bei Height- oder Bump-Mapping</param>
	///<param name="vBitangent">Oberfl�chenbitangente des Vertex (W-Faktor muss 0 sein!), wichtig bei Height- oder Bump-Mapping</param>
	///<param name="fU">U-Komponente der UV-Texturparameter</param>
	///<param name="fV">V-Komponente der UV-Texturparameter</param>
	void Init(CHVector & vPos, CHVector & vNormal, CHVector & vTangent, CHVector & vBitangent, float fU = 0, float fV = 0);

	///<summary> Deinitialisiert den Vertex.</summary>
	void Fini();

	///<summary> Verschmilzt Normalen-, Tangenten- und Bitangenteninformationen der beiden Vertices this und vertex2.</summary>
	///<param name="vertex">Zu verschmelzender Vertex</param>
	void UniteDirections(CVertex & vertex);

	///<summary> Matrixmultiplikation aller Werte mit der Matrix m => Verschieben, Rotieren, Skalieren etc. m�glich.</summary>
	///<param name="m">Homogene Transformationsmatrix</param>
	void Transform(CHMat &m);

	///<summary> Matrixmultiplikation aller Werte mit der Matrix m => Verschieben, Rotieren, Skalieren etc. m�glich, schneller als Transform, aber bei Skalierungen und Spiegelungen werden Normalenvektoren falsch berechnet.</summary>
	///<param name="m">Homogene Transformationsmatrix</param>
	void TransformScaleless(CHMat &m);

	///<summary> Matrixmultiplikation der Normalen-, der Tangenten- und der Bitangentenvektoren, Position und UV-Koordinaten werden belassen.</summary>
	///<param name="m">Homogene Transformationsmatrix</param>
	void TransformDirections(CHMat &m); 

	///<summary> Versucht, die Tangenten und die Bitangenten f�r das Bumpmapping aus den gegebenen UV-Koordianten der zwei aufeinanderfolgenden Vertices im Dreeick zu berechnen.<para></para>
	/// Achtung:  Es kann sich nur um eine N�herungsl�sung handeln! </summary>
	///<param name="vertex1">N�chster Vertex im Dreieckspolygon</param>
	///<param name="vertex2">�bern�chster Vertex (= vorheriger Vertex) im Dreieckspolygon</param>
	void EstimateTangentAndBitangent(CVertex & vertex1, CVertex & vertex2);
	
	///<summary> Versucht, die Tangenten und die Bitangenten f�r das Bumpmapping aus den gegebenen UV-Koordianten der zwei aufeinanderfolgenden Vertices im Dreeick zu berechnen, <para></para>
	/// addiert die berechneten Werte auf die vorhandenen Tangenten und Bitangenten.<para></para>
	/// Achtung:  Es kann sich nur um eine N�herungsl�sung handeln! </summary>
	///<param name="vertex1">N�chster Vertex im Dreieckspolygon</param>
	///<param name="vertex2">�bern�chster Vertex (= vorheriger Vertex) im Dreieckspolygon</param>
	void EstimateTangentAndBitangentOffset(CVertex & vertex1, CVertex & vertex2);

	///<summary> Setzt Tangente und Bitangente auf Null (0,0,0,0).</summary>
	void ClearTangentAndBitangent();

	///<summary> Interpoliert zwischen Vertex A und Vertex B.</summary>
	///<param name="vertexA">Ausgags-Vertex A</param>
	///<param name="vertexA">Ziel-Vertex B</param>
	///<param name="fr">Laufparameter</param>
	void Interpol(CVertex & vertexA, CVertex & vertexB, float fr, bool bInterpolateNormals = true, bool bInterpolateTangentsAndBitangents = true, bool bInterpolateUV = true);

	///<summary> F�gt dem Vertex eine Facette hinzu, die den Vertex als Eckpunkt hat (optional).</summary>
	///<param name="pface">Pointer zu einem adjazenten Face </param>
	void AddFace(CFace * pface);

	///<summary> H�ngt vom Vertex eine Facette wieder ab, gibt true aus, falls es geklappt hat.</summary>
	///<param name="pface">Pointer zu einem adjazenten Face </param>
	bool SubFace(CFace * pface);

	///<summary> F�gt dem Vertex einen anderen Vertex hinzu, der dieselbe Position hat (optional).</summary>
	///<param name="pvertexSame">Pointer zu einem Vertex, der dieselbe Position hat </param>
	void AddVertexSame(CVertex * pvertexSame);

	///<summary> H�ngt vom Vertex einen anderen Vertex ab, gibt true aus, falls es geklappt hat.</summary>
	///<param name="pvertexSame">Pointer zu einem Vertex, der dieselbe Position hat </param>
	bool SubVertexSame(CVertex * pvertexSame);

	///<summary> L�scht die Liste auf die gleichen Vertices.</summary>
	void SubAllVerticesSame();

	///<summary> Berechnet Vertexnormale aus den drei adjazenten Fl�chennormalen, so dass Objekt nach dem Shading gerundet erscheint.</summary>
	void Smooth();

	///<summary> L�scht alle Topologiedaten (zus�tzliche Informationen zu adjazenten Faces und �hnlichen Vertices)).</summary>
	void ClearTopology();

	///<summary> Gibt den aktuellen Vertexstatus im Logfile aus. </summary>
	void Log();

	///<summary> Gibt true aus, falls die Oberfl�che am Vertex mannigfaltig ist. </summary>
	///<param name="pvertexNext">Pointer zum n�chchsten nichtmannigfaligen Vertex (rechtsh�ndige Drehrichtung), falls der Vertex mannigfaltig wird ein Nullptr ausgegeben </param>
	bool IsManifold(CVertex * pvertexNext);

	///<summary> Pointer zum n�chchsten nichtmannigfaligen Vertex (rechtsh�ndige Drehrichtung), falls der Vertex mannigfaltig wird ein Nullptr ausgegeben. </summary>
	///<param name="pvertexNext">Pointer zum n�chchsten nichtmannigfaligen Vertex (rechtsh�ndige Drehrichtung), falls der Vertex mannigfaltig wird ein Nullptr ausgegeben </param>
	CVertex * IsManifold();

	///<summary> Gibt true aus, wenn die vorliegende Vektorposition auf der Geraden zwischen zwei anderen Vertices liegt.</summary> 
	///<param name="vertexA">Vertex A</param>
	///<param name="vertexB">Vertex B</param>
	///<param name="fAccuracyThreshold">Genauigkeitsschwelle, je gr��er, desto mehr darf der Punkt von der genauen Geraden abweichen.</param>
	bool IsBetween(CVertex & vertexA, CVertex & vertexB, float fAccuracyThreshold = 0.001f);


	///<summary> Gibt das n�chste adjazente Face (rechtsh�ndige Drehrichtung) zu pface aus. </summary>
	///<param name="pface">Ausgangsface, zu dem das n�chste Face gesucht wird </param>
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

	///<summary> U-Koordinate f�r das UV-Mapping.</summary>
	float m_fU; 

	///<summary> V-Koordinate f�r das UV-Mapping.</summary>
	float m_fV;

	///<summary> Markierungsflag, f�r viele verschiedene Algorithmen sinnvoll. Sollte nach Ausf�hrung des Algorithmus wieder auf Null gesetzt werden.</summary>
	bool m_bMarked;

	///<summary> Optionale Liste von anderen Vertices mit gleicher Position.</summary>
	CVertexs * m_pverticesSame;

	///<summary> Optionale Liste der Faces, die an den Vertex angrenzen.</summary>
	CFaces * m_pfaces;


};

}