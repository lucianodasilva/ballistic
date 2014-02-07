bl_info = {
    "name":         "Ballistic XML",
    "author":       "Luciano da Silva",
    "blender":      (2,6,9),
    "version":      (0,0,1),
    "location":     "File > Import-Export",
    "description":  "Export custom data format",
    "category":     "Import-Export"
}
        
import bpy
from bpy_extras.io_utils import ExportHelper

# -------------------------------------------------------
# Ballistic Classes
# -------------------------------------------------------

class vec3:
    x = .0
    y = .0
    z = .0

    def __init__ (self, vlist):
        self.x = vlist [0]
        self.y = vlist [1]
        self.z = vlist [2]

    def __eq__(self, other):
        return (self.x == other.x) and (self.y == other.y) and (self.z == other.z)

    def print_out (self, output_file):
        output_file.write ("%f,%f,%f" % (self.x, self.y, self.z))

class vec2:
    x = .0
    y = .0

    def __init__ (self, vlist):
        self.x = vlist [0]
        self.y = vlist [1]

    def __eq__(self, other):
        return (self.x == other.x) and (self.y == other.y)

    def print_out (self, output_file):
        output_file.write ("%f,%f" % (self.x, self.y))

class vector:
    position = vec3 ([.0,.0,.0])
    normal = vec3 ([.0, .0, .0])
    uv = vec2 ([.0, .0])

    def __init__ (self, posv, normv, uvv):
        self.position = posv
        self.normal = normv
        self.uv = uvv

    def __eq__ (self, other):
        return (self.position == other.position) and (self.normal == other.normal) and (self.uv == other.uv)

class color:
    r = .0
    g = .0
    b = .0

    def __init__ (self, vlist):
        self.r = vlist [0]
        self.g = vlist [1]
        self.b = vlist [2]

    def print_out (self, output_file):
        output_file.write ("\"%f,%f,%f,1.\"" % (self.r, self.g, self.b))

class material:
    name = ""
    diffuse = color ([.0, .0, .0])
    specular = color ([.0, .0, .0])
    opacity = 1.0
    texture = ""

    def __init__ (self, namev, difv, specv, opacv, texv):
        self.name = namev
        self.diffuse = difv
        self.specular = specv
        self.opacity = opacv
        self.texture = texv

    def print_out (self, output_file):
        output_file.write ("\t<material name=\"%s\" diffuse=" % self.name)
        self.diffuse.print_out (output_file)
        output_file.write (" specular=")
        self.specular.print_out (output_file)
        output_file.write (" opacity=\"%f\" texture=\"%s\" />\n" % (self.opacity, self.texture))

# -------------------------------------------------------
# export model
# -------------------------------------------------------

def unfold_vectors (mesh, poly, poly_uv):
    vectors = []

    uv_index = 0;

    for vi in poly.vertices:
        pos_co = mesh.vertices [vi].co
        norm_co = []

        if (poly.use_smooth):
            norm_co = mesh.vertices [vi].normal
        else:
            norm_co = poly.normal

        pos = vec3 (pos_co)
        norm = vec3 (norm_co)

        uv = vec2 (poly_uv.uv [uv_index])
        uv_index += 1
        vectors.append (vector (pos, norm, uv))

    return vectors

def find_index (vectors, vec):
    index = 0
    for item in vectors:
        if vec == item:
            return index
        index += 1

    index = len (vectors)
    vectors.append (vec)
    return index

def write_model (obj, output_file):

    mesh = obj.data
    # prepare data
    mesh.update (False, True)

    faces = mesh.tessfaces
    # expect it to exist -- handle later
    uv_face = mesh.tessface_uv_textures [0]

    b_vectors = []
    b_vector_indexes = []

    for poly, uv in zip (mesh.tessfaces, uv_face.data):

        # create vectors
        vectors = unfold_vectors (mesh, poly, uv)

        if len (vectors) == 3:
            b_vector_indexes.append (find_index (b_vectors, vectors [0]))
            b_vector_indexes.append (find_index (b_vectors, vectors [1]))
            b_vector_indexes.append (find_index (b_vectors, vectors [2]))
        else:
            b_vector_indexes.append (find_index (b_vectors, vectors [0]))
            b_vector_indexes.append (find_index (b_vectors, vectors [1]))
            b_vector_indexes.append (find_index (b_vectors, vectors [2]))
            b_vector_indexes.append (find_index (b_vectors, vectors [0]))
            b_vector_indexes.append (find_index (b_vectors, vectors [2]))
            b_vector_indexes.append (find_index (b_vectors, vectors [3]))

    # write data
    output_file.write ("\t<mesh name=\"%s\">\n" % obj.name)

    write_elements (output_file, "position", b_vectors )
    write_elements (output_file, "normal", b_vectors )
    write_elements (output_file, "uv", b_vectors )

    # write indexes
    output_file.write ("\t\t<index>")
    first = True;
    for idx in b_vector_indexes:
        if first:
            first = False
        else:
            output_file.write (',')
        output_file.write("%i" % idx)
    output_file.write ("</index>\n")

    output_file.write ("\t</mesh>\n")


def write_elements (output_file, id, buffer):
    output_file.write ("\t\t<%s>" % id)
    first = True;

    for v_item in buffer:
        member_item = getattr (v_item, id)

        if first:
            first = False
        else:
            output_file.write (',')

        member_item.print_out (output_file)

    output_file.write ("</%s>\n" % id)

def write_materials (output_file):
    for mat in bpy.data.materials:

        texture = ""
        if len (mat.texture_slots) > 0:
            texture = mat.texture_slots[0].name

        b_mat = material (mat.name, color (mat.diffuse_color), color (mat.specular_color), mat.translucency, texture)
        b_mat.print_out (output_file)

# -------------------------------------------------------

class ExportMyFormat(bpy.types.Operator, ExportHelper):
    bl_idname       = "export_my_format.xml"
    bl_label        = "Ballistic Model Data Exporter"
    bl_options      = {'PRESET'}
    
    filename_ext    = ".xml"

    # -------------------------------------------------------
    
    def execute(self, context):

        bpy.ops.object.mode_set(mode='OBJECT')

        scene = context.scene
        selection = []

        for ob in scene.objects:
            if ob.is_visible(scene) and ob.select and ob.type == 'MESH':
                selection.append (ob)
        
        if len (selection) != 1:
            raise NameError ("A single mesh object should be selected for export")

        obj = selection[0]

        out_file = open (self.filepath, 'w')
        out_file.write ("<package>\n")
        
        write_materials (out_file)
        write_model (obj, out_file)

        out_file.write ("</package>\n")
        out_file.close ()
        return {'FINISHED'}

    def draw (self, context):
        # layout = self.layout

        # obj = context.object
        
        # row = layout.row ()
        # row.label (text = "Hello world!", icon='WORLD_DATA')

        # row = layout.row ()
        # row.label (text="Active object is: " + obj.name)

        # row = layout.row ()
        # row.prop (obj, "name")

        # row = layout.row ()
        # row.operator ("mesh.primitive_cube_add")

def menu_func(self, context):
    self.layout.operator(ExportMyFormat.bl_idname, text="Ballistic Model Format(.xml)")

def register():
    bpy.utils.register_module(__name__)
    bpy.types.INFO_MT_file_export.append(menu_func)
    
def unregister():
    bpy.utils.unregister_module(__name__)
    bpy.types.INFO_MT_file_export.remove(menu_func)

if __name__ == "__main__":
    register()
