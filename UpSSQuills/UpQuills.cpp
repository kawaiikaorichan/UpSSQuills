#include "pch.h"
#include "SSHeads.h"
#include "ModelInfo.h"
#include "lanternapi.h"
#include "Trampoline.h"

NJS_MATERIAL* TemporaryMaterialArray[] = { nullptr };

NJS_MATERIAL* Specular2[] = {
	&matlist_attach_00008DC4[0],
	&matlist_attach_00008DC4[1],
	&matlist_attach_00008DC4[2],
	&matlist_attach_00008DC4[3],
};

bool ForceDiffuse2Specular2(NJS_MATERIAL* material, Uint32 flags)
{
	set_diffuse(2, false);
	set_specular(2, false);
	return true;
}

void ForceDiffuse2Specular2_Object(NJS_OBJECT* obj)
{
	if (obj->basicdxmodel)
	{
		for (int q = 0; q < obj->basicdxmodel->nbMat; ++q)
		{
			if (!(obj->basicdxmodel->mats[q].attrflags & NJD_FLAG_IGNORE_LIGHT))
			{
				TemporaryMaterialArray[0] = &obj->basicdxmodel->mats[q];
				material_register(TemporaryMaterialArray, 1, ForceDiffuse2Specular2);
			}
		}
	}
	if (obj->child) ForceDiffuse2Specular2_Object(obj->child);
	if (obj->sibling) ForceDiffuse2Specular2_Object(obj->sibling);
}

extern "C" __declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions & helperFunctions)
{
	HMODULE handle = GetModuleHandle(L"CHRMODELS_orig");
	NJS_OBJECT** ___SONIC_OBJECTS = (NJS_OBJECT**)GetProcAddress(handle, "___SONIC_OBJECTS");
	HMODULE Lantern = GetModuleHandle(L"sadx-dc-lighting");
	HMODULE DCcharacters = GetModuleHandle(L"SA1_Chars");
	HMODULE DXrefined = GetModuleHandle(L"SADXR");

	if (DCcharacters)
	{
		SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling->sibling->child->child->sibling->sibling->sibling->model = &attach_00008DC4;
	}

	else if (DXrefined)
	{
		SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling->sibling->child->child->sibling->sibling->sibling->model = &attach_0062C4A0r;
	}

	else
	{
		SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling->sibling->child->child->sibling->sibling->sibling->model = &attach_0062C4A0;
	}

	if (Lantern)
	{
		material_register(Specular2, LengthOfArray(Specular2), &ForceDiffuse2Specular2);
	}
}

extern "C" __declspec(dllexport) const ModInfo SADXModInfo = { ModLoaderVer };