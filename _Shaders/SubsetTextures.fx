matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;


texture AlbedoTex0;
texture AlbedoTex1;
texture AlbedoTex2;
texture AlbedoTex3;
texture AlbedoTex4;
texture AlbedoTex5;
texture AlbedoTex6;
texture AlbedoTex7;
texture AlbedoTex8;
texture AlbedoTex9;
texture AlbedoTex10;
texture AlbedoTex11;
texture AlbedoTex12;
texture AlbedoTex13;
texture AlbedoTex14;
texture AlbedoTex15;
texture AlbedoTex16;
texture AlbedoTex17;
texture AlbedoTex18;
texture AlbedoTex19;
texture AlbedoTex20;
texture AlbedoTex21;
texture AlbedoTex22;
texture AlbedoTex23;
texture AlbedoTex24;
texture AlbedoTex25;
texture AlbedoTex26;
texture AlbedoTex27;
texture AlbedoTex28;
texture AlbedoTex29;

sampler AlbedoSampler[15] =
{
	sampler_state { Texture = (AlbedoTex0); },
	sampler_state { Texture = (AlbedoTex1); },
	sampler_state { Texture = (AlbedoTex2); },
	sampler_state { Texture = (AlbedoTex3); },
	sampler_state { Texture = (AlbedoTex4); },
	sampler_state { Texture = (AlbedoTex5); },
	sampler_state { Texture = (AlbedoTex6); },
	sampler_state { Texture = (AlbedoTex7); },
	sampler_state { Texture = (AlbedoTex8); },
	sampler_state { Texture = (AlbedoTex9); },
	sampler_state { Texture = (AlbedoTex10); },
	sampler_state { Texture = (AlbedoTex11); },
	sampler_state { Texture = (AlbedoTex12); },
	sampler_state { Texture = (AlbedoTex13); },
	sampler_state { Texture = (AlbedoTex14); },
	//sampler_state { Texture = (AlbedoTex15); }
	/*sampler_state { Texture = (AlbedoTex16); },
	sampler_state { Texture = (AlbedoTex17); },
	sampler_state { Texture = (AlbedoTex18); },
	sampler_state { Texture = (AlbedoTex19); },
	sampler_state { Texture = (AlbedoTex20); },
	sampler_state { Texture = (AlbedoTex21); },
	sampler_state { Texture = (AlbedoTex22); },
	sampler_state { Texture = (AlbedoTex23); },
	sampler_state { Texture = (AlbedoTex24); },
	sampler_state { Texture = (AlbedoTex25); },
	sampler_state { Texture = (AlbedoTex26); },
	sampler_state { Texture = (AlbedoTex27); },
	sampler_state { Texture = (AlbedoTex28); },
	sampler_state { Texture = (AlbedoTex29); }*/
};


texture NormalTex0;
texture NormalTex1;
texture NormalTex2;
texture NormalTex3;
texture NormalTex4;
texture NormalTex5;
texture NormalTex6;
texture NormalTex7;
texture NormalTex8;
texture NormalTex9;
texture NormalTex10;
texture NormalTex11;
texture NormalTex12;
texture NormalTex13;
texture NormalTex14;
texture NormalTex15;
texture NormalTex16;
texture NormalTex17;
texture NormalTex18;
texture NormalTex19;
texture NormalTex20;
texture NormalTex21;
texture NormalTex22;
texture NormalTex23;
texture NormalTex24;
texture NormalTex25;
texture NormalTex26;
texture NormalTex27;
texture NormalTex28;
texture NormalTex29;

sampler NormalSampler[15] =
{
	sampler_state { Texture = (NormalTex0); },
	sampler_state { Texture = (NormalTex1); },
	sampler_state { Texture = (NormalTex2); },
	sampler_state { Texture = (NormalTex3); },
	sampler_state { Texture = (NormalTex4); },
	sampler_state { Texture = (NormalTex5); },
	sampler_state { Texture = (NormalTex6); },
	sampler_state { Texture = (NormalTex7); },
	sampler_state { Texture = (NormalTex8); },
	sampler_state { Texture = (NormalTex9); },
	sampler_state { Texture = (NormalTex10); },
	sampler_state { Texture = (NormalTex11); },
	sampler_state { Texture = (NormalTex12); },
	sampler_state { Texture = (NormalTex13); },
	sampler_state { Texture = (NormalTex14); },
	//sampler_state { Texture = (NormalTex15); }
	/*sampler_state { Texture = (NormalTex16); },
	sampler_state { Texture = (NormalTex17); },
	sampler_state { Texture = (NormalTex18); },
	sampler_state { Texture = (NormalTex19); },
	sampler_state { Texture = (NormalTex20); },
	sampler_state { Texture = (NormalTex21); },
	sampler_state { Texture = (NormalTex22); },
	sampler_state { Texture = (NormalTex23); },
	sampler_state { Texture = (NormalTex24); },
	sampler_state { Texture = (NormalTex25); },
	sampler_state { Texture = (NormalTex26); },
	sampler_state { Texture = (NormalTex27); },
	sampler_state { Texture = (NormalTex28); },
	sampler_state { Texture = (NormalTex29); }*/
};

/* Specular */
// rgb = specularMap
// a = specularMask
texture SpecularTex0;
texture SpecularTex1;
texture SpecularTex2;
texture SpecularTex3;
texture SpecularTex4;
texture SpecularTex5;
texture SpecularTex6;
texture SpecularTex7;
texture SpecularTex8;
texture SpecularTex9;
texture SpecularTex10;
texture SpecularTex11;
texture SpecularTex12;
texture SpecularTex13;
texture SpecularTex14;
texture SpecularTex15;
texture SpecularTex16;
texture SpecularTex17;
texture SpecularTex18;
texture SpecularTex19;
texture SpecularTex20;
texture SpecularTex21;
texture SpecularTex22;
texture SpecularTex23;
texture SpecularTex24;
texture SpecularTex25;
texture SpecularTex26;
texture SpecularTex27;
texture SpecularTex28;
texture SpecularTex29;

sampler SpecularSampler[15] =
{
	sampler_state { Texture = (SpecularTex0); },
	sampler_state { Texture = (SpecularTex1); },
	sampler_state { Texture = (SpecularTex2); },
	sampler_state { Texture = (SpecularTex3); },
	sampler_state { Texture = (SpecularTex4); },
	sampler_state { Texture = (SpecularTex5); },
	sampler_state { Texture = (SpecularTex6); },
	sampler_state { Texture = (SpecularTex7); },
	sampler_state { Texture = (SpecularTex8); },
	sampler_state { Texture = (SpecularTex9); },
	sampler_state { Texture = (SpecularTex10); },
	sampler_state { Texture = (SpecularTex11); },
	sampler_state { Texture = (SpecularTex12); },
	sampler_state { Texture = (SpecularTex13); },
	sampler_state { Texture = (SpecularTex14); },
	//sampler_state { Texture = (SpecularTex15); }
	//sampler_state { Texture = (SpecularTex16); },
	//sampler_state { Texture = (SpecularTex17); },
	//sampler_state { Texture = (SpecularTex18); },
	//sampler_state { Texture = (SpecularTex19); },
	//sampler_state { Texture = (SpecularTex20); },
	//sampler_state { Texture = (SpecularTex21); },
	//sampler_state { Texture = (SpecularTex22); },
	//sampler_state { Texture = (SpecularTex23); },
	//sampler_state { Texture = (SpecularTex24); },
	//sampler_state { Texture = (SpecularTex25); },
	//sampler_state { Texture = (SpecularTex26); },
	//sampler_state { Texture = (SpecularTex27); },
	//sampler_state { Texture = (SpecularTex28); },
	//sampler_state { Texture = (SpecularTex29); }
};

texture EmissiveTex0;
texture EmissiveTex1;
texture EmissiveTex2;
texture EmissiveTex3;
texture EmissiveTex4;
texture EmissiveTex5;
texture EmissiveTex6;
texture EmissiveTex7;
texture EmissiveTex8;
texture EmissiveTex9;
texture EmissiveTex10;
texture EmissiveTex11;
texture EmissiveTex12;
texture EmissiveTex13;
texture EmissiveTex14;
texture EmissiveTex15;
texture EmissiveTex16;
texture EmissiveTex17;
texture EmissiveTex18;
texture EmissiveTex19;
texture EmissiveTex20;
texture EmissiveTex21;
texture EmissiveTex22;
texture EmissiveTex23;
texture EmissiveTex24;
texture EmissiveTex25;
texture EmissiveTex26;
texture EmissiveTex27;
texture EmissiveTex28;
texture EmissiveTex29;

sampler EmissiveSampler[15] =
{
	sampler_state { Texture = (EmissiveTex0); },
	sampler_state { Texture = (EmissiveTex1); },
	sampler_state { Texture = (EmissiveTex2); },
	sampler_state { Texture = (EmissiveTex3); },
	sampler_state { Texture = (EmissiveTex4); },
	sampler_state { Texture = (EmissiveTex5); },
	sampler_state { Texture = (EmissiveTex6); },
	sampler_state { Texture = (EmissiveTex7); },
	sampler_state { Texture = (EmissiveTex8); },
	sampler_state { Texture = (EmissiveTex9); },
	sampler_state { Texture = (EmissiveTex10); },
	sampler_state { Texture = (EmissiveTex11); },
	sampler_state { Texture = (EmissiveTex12); },
	sampler_state { Texture = (EmissiveTex13); },
	sampler_state { Texture = (EmissiveTex14); },
	//sampler_state { Texture = (EmissiveTex15); }
	/*sampler_state { Texture = (EmissiveTex16); },
	sampler_state { Texture = (EmissiveTex17); },
	sampler_state { Texture = (EmissiveTex18); },
	sampler_state { Texture = (EmissiveTex19); },
	sampler_state { Texture = (EmissiveTex20); },
	sampler_state { Texture = (EmissiveTex21); },
	sampler_state { Texture = (EmissiveTex22); },
	sampler_state { Texture = (EmissiveTex23); },
	sampler_state { Texture = (EmissiveTex24); },
	sampler_state { Texture = (EmissiveTex25); },
	sampler_state { Texture = (EmissiveTex26); },
	sampler_state { Texture = (EmissiveTex27); },
	sampler_state { Texture = (EmissiveTex28); },
	sampler_state { Texture = (EmissiveTex29); }*/
};

texture SpecularMaskTex0;
texture SpecularMaskTex1;
texture SpecularMaskTex2;
texture SpecularMaskTex3;
texture SpecularMaskTex4;
texture SpecularMaskTex5;
texture SpecularMaskTex6;
texture SpecularMaskTex7;
texture SpecularMaskTex8;
texture SpecularMaskTex9;
texture SpecularMaskTex10;
texture SpecularMaskTex11;
texture SpecularMaskTex12;
texture SpecularMaskTex13;
texture SpecularMaskTex14;
texture SpecularMaskTex15;
texture SpecularMaskTex16;
texture SpecularMaskTex17;
texture SpecularMaskTex18;
texture SpecularMaskTex19;
texture SpecularMaskTex20;
texture SpecularMaskTex21;
texture SpecularMaskTex22;
texture SpecularMaskTex23;
texture SpecularMaskTex24;
texture SpecularMaskTex25;
texture SpecularMaskTex26;
texture SpecularMaskTex27;
texture SpecularMaskTex28;
texture SpecularMaskTex29;

sampler SpecularMaskSampler[15] =
{
	sampler_state { Texture = (SpecularMaskTex0); },
	sampler_state { Texture = (SpecularMaskTex1); },
	sampler_state { Texture = (SpecularMaskTex2); },
	sampler_state { Texture = (SpecularMaskTex3); },
	sampler_state { Texture = (SpecularMaskTex4); },
	sampler_state { Texture = (SpecularMaskTex5); },
	sampler_state { Texture = (SpecularMaskTex6); },
	sampler_state { Texture = (SpecularMaskTex7); },
	sampler_state { Texture = (SpecularMaskTex8); },
	sampler_state { Texture = (SpecularMaskTex9); },
	sampler_state { Texture = (SpecularMaskTex10); },
	sampler_state { Texture = (SpecularMaskTex11); },
	sampler_state { Texture = (SpecularMaskTex12); },
	sampler_state { Texture = (SpecularMaskTex13); },
	sampler_state { Texture = (SpecularMaskTex14); },
	//sampler_state { Texture = (SpecularMaskTex15); }
	/*sampler_state { Texture = (SpecularMaskTex16); },
	sampler_state { Texture = (SpecularMaskTex17); },
	sampler_state { Texture = (SpecularMaskTex18); },
	sampler_state { Texture = (SpecularMaskTex19); },
	sampler_state { Texture = (SpecularMaskTex20); },
	sampler_state { Texture = (SpecularMaskTex21); },
	sampler_state { Texture = (SpecularMaskTex22); },
	sampler_state { Texture = (SpecularMaskTex23); },
	sampler_state { Texture = (SpecularMaskTex24); },
	sampler_state { Texture = (SpecularMaskTex25); },
	sampler_state { Texture = (SpecularMaskTex26); },
	sampler_state { Texture = (SpecularMaskTex27); },
	sampler_state { Texture = (SpecularMaskTex28); },
	sampler_state { Texture = (SpecularMaskTex29); }*/
};

texture DiffuseMaskTex0;
texture DiffuseMaskTex1;
texture DiffuseMaskTex2;
texture DiffuseMaskTex3;
texture DiffuseMaskTex4;
texture DiffuseMaskTex5;
texture DiffuseMaskTex6;
texture DiffuseMaskTex7;
texture DiffuseMaskTex8;
texture DiffuseMaskTex9;
texture DiffuseMaskTex10;
texture DiffuseMaskTex11;
texture DiffuseMaskTex12;
texture DiffuseMaskTex13;
texture DiffuseMaskTex14;
texture DiffuseMaskTex15;
texture DiffuseMaskTex16;
texture DiffuseMaskTex17;
texture DiffuseMaskTex18;
texture DiffuseMaskTex19;
texture DiffuseMaskTex20;
texture DiffuseMaskTex21;
texture DiffuseMaskTex22;
texture DiffuseMaskTex23;
texture DiffuseMaskTex24;
texture DiffuseMaskTex25;
texture DiffuseMaskTex26;
texture DiffuseMaskTex27;
texture DiffuseMaskTex28;
texture DiffuseMaskTex29;

sampler DiffuseMaskSampler[15] =
{
	sampler_state { Texture = (DiffuseMaskTex0); },
	sampler_state { Texture = (DiffuseMaskTex1); },
	sampler_state { Texture = (DiffuseMaskTex2); },
	sampler_state { Texture = (DiffuseMaskTex3); },
	sampler_state { Texture = (DiffuseMaskTex4); },
	sampler_state { Texture = (DiffuseMaskTex5); },
	sampler_state { Texture = (DiffuseMaskTex6); },
	sampler_state { Texture = (DiffuseMaskTex7); },
	sampler_state { Texture = (DiffuseMaskTex8); },
	sampler_state { Texture = (DiffuseMaskTex9); },
	sampler_state { Texture = (DiffuseMaskTex10); },
	sampler_state { Texture = (DiffuseMaskTex11); },
	sampler_state { Texture = (DiffuseMaskTex12); },
	sampler_state { Texture = (DiffuseMaskTex13); },
	sampler_state { Texture = (DiffuseMaskTex14); },
	//sampler_state { Texture = (DiffuseMaskTex15); }
	/*sampler_state { Texture = (DiffuseMaskTex16); },
	sampler_state { Texture = (DiffuseMaskTex17); },
	sampler_state { Texture = (DiffuseMaskTex18); },
	sampler_state { Texture = (DiffuseMaskTex19); },
	sampler_state { Texture = (DiffuseMaskTex20); },
	sampler_state { Texture = (DiffuseMaskTex21); },
	sampler_state { Texture = (DiffuseMaskTex22); },
	sampler_state { Texture = (DiffuseMaskTex23); },
	sampler_state { Texture = (DiffuseMaskTex24); },
	sampler_state { Texture = (DiffuseMaskTex25); },
	sampler_state { Texture = (DiffuseMaskTex26); },
	sampler_state { Texture = (DiffuseMaskTex27); },
	sampler_state { Texture = (DiffuseMaskTex28); },
	sampler_state { Texture = (DiffuseMaskTex29); }*/
};
