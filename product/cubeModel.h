Vec3 triangle_env_material(0.9, 0.9, 0.9); // Material's enviroment component factors
Vec3 triangle_dif_material(0.9, 0.9, 0.9);   // Material's difuse component factors
Vec3 triangle_spe_material(0.9, 0.9, 0.9);   // Material's specular component factors
Material triangle_material(triangle_env_material, triangle_dif_material, triangle_spe_material);
vector<Triangle> faces= { Triangle( Point( 1, -1, -1 ), Point( 1, -1, 1 ), Point( -1, -1, 1 ), triangle_material ), 
Triangle( Point( 1, -1, -1 ), Point( -1, -1, 1 ), Point( -1, -1, -1 ), triangle_material ), 
Triangle( Point( 1, 1, -0.999999 ), Point( -1, 1, -1 ), Point( -1, 1, 1 ), triangle_material ), 
Triangle( Point( 1, 1, -0.999999 ), Point( -1, 1, 1 ), Point( 0.999999, 1, 1 ), triangle_material ), 
Triangle( Point( 1, -1, -1 ), Point( 1, 1, -0.999999 ), Point( 0.999999, 1, 1 ), triangle_material ), 
Triangle( Point( 1, -1, -1 ), Point( 0.999999, 1, 1 ), Point( 1, -1, 1 ), triangle_material ), 
Triangle( Point( 1, -1, 1 ), Point( 0.999999, 1, 1 ), Point( -1, 1, 1 ), triangle_material ), 
Triangle( Point( 1, -1, 1 ), Point( -1, 1, 1 ), Point( -1, -1, 1 ), triangle_material ), 
Triangle( Point( -1, -1, 1 ), Point( -1, 1, 1 ), Point( -1, 1, -1 ), triangle_material ), 
Triangle( Point( -1, -1, 1 ), Point( -1, 1, -1 ), Point( -1, -1, -1 ), triangle_material ), 
Triangle( Point( 1, 1, -0.999999 ), Point( 1, -1, -1 ), Point( -1, -1, -1 ), triangle_material ), 
Triangle( Point( 1, 1, -0.999999 ), Point( -1, -1, -1 ), Point( -1, 1, -1 ), triangle_material ), 
}; 
