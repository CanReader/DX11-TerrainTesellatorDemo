// texture.cpp
#include "texture.h"

Texture::Texture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, WCHAR* filename)
{
	m_texture = nullptr;
	HRESULT result;

	// If no filename or file doesn't exist, create a fallback texture
	if (!filename || !does_file_exist(filename))
	{
		if (createFallbackTexture(device))
			return;
		MessageBox(NULL, L"Failed to create fallback texture", L"ERROR", MB_OK);
		return;
	}

	// check file extension for correct loading function.
	std::wstring fn(filename);
	std::string::size_type idx;
	std::wstring extension;

	idx = fn.rfind('.');

	if (idx != std::string::npos)
	{
		extension = fn.substr(idx + 1);
	}

	// Load the texture in.
	if (extension == L"dds")
	{
		result = CreateDDSTextureFromFile(device, deviceContext, filename, NULL, &m_texture, 0, NULL);
	}
	else
	{
		result = CreateWICTextureFromFile(device, deviceContext, filename, NULL, &m_texture, 0);
	}

	if (FAILED(result))
	{
		// File exists but failed to load - try fallback
		if (!createFallbackTexture(device))
		{
			MessageBox(NULL, L"Texture loading error", L"ERROR", MB_OK);
		}
	}
}

Texture::~Texture()
{
	// Release the texture resource.
	if (m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}
}


ID3D11ShaderResourceView* Texture::GetTexture()
{
	return m_texture;
}

bool Texture::does_file_exist(const WCHAR *fname)
{
	std::ifstream infile(fname);
	return infile.good();
}

bool Texture::createFallbackTexture(ID3D11Device* device)
{
	// Create a simple 2x2 checkerboard texture as fallback
	const UINT width = 2;
	const UINT height = 2;
	// Magenta/black checkerboard to make missing textures obvious
	UINT32 pixels[4] = {
		0xFFFF00FF, 0xFF000000,
		0xFF000000, 0xFFFF00FF
	};

	D3D11_TEXTURE2D_DESC texDesc = {};
	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texDesc.SampleDesc.Count = 1;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = pixels;
	initData.SysMemPitch = width * sizeof(UINT32);

	ID3D11Texture2D* tex = nullptr;
	HRESULT hr = device->CreateTexture2D(&texDesc, &initData, &tex);
	if (FAILED(hr))
		return false;

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = texDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	hr = device->CreateShaderResourceView(tex, &srvDesc, &m_texture);
	tex->Release();

	return SUCCEEDED(hr);
}
