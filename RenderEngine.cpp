#include "RenderEngine.h"

//////////////////////////////////////////////////////////////////


RenderFunction::RenderFunction(RenderSettings& rendSett, Scene& scene, std::vector<float3>& points) :
	m_rendSett(rendSett),
	m_scene(scene),
	m_points(points)
{
	m_points.resize(rendSett.m_maxSamples);
}


void RenderFunction::Render()
{
	Sampling sampling(m_rendSett.m_sampMtd);

	const int maxDim = 3;
	std::vector<float> rndNums(3);

	for (int i = 0; i < m_rendSett.m_maxSamples; ++i)
	{		
		for (size_t dim = 0; dim < maxDim; ++dim)
		{
			rndNums[dim] = sampling.GetOneRndDigit(i, dim);
			rndNums[dim] = sampling.GetOneRndDigit(i, dim);
			rndNums[dim] = sampling.GetOneRndDigit(i, dim);
		}

		m_points[i] = m_scene.Eval(rndNums);
	}
}





