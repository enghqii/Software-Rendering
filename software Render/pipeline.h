
class PipeLine{
public:
	PipeLine(){}
	~PipeLine(){}
	void LocalSpace();
	void WorldSpace();
	void ViewSpace();
	void BackfaceCulling();
	void Lighting();
	void Clipping();
	void Projection();
	void ViewPort();
	void Rasterize();
private:
};